#include "AnimatedModelLoader.h"
#include "../../../util/FileReader.h"
#include "../../../util/StringUtils.h"

AnimatedModelLoader::AnimatedModelLoader(): currentBoneIndex(0), rotationMatrix(Mat4().rotateX(-M_PI_2)) {}

AnimatedModel *AnimatedModelLoader::load(const std::string &path) {
    std::string content = FileReader::getContent(path);

    std::string materialContent = getContent("library_effects", content);
    std::string geometryContent = getContent("library_geometries", content);
    std::string shapeContent = getContent("library_visual_scenes", content);
    std::string jointContent = getContent("library_controllers", content);
    std::string keyframeContent;

    try {
        keyframeContent = getContent("library_animations", content);
    } catch (...) {

    }

    Joint* rootJoint = getJointHierarchy(shapeContent);

    auto meshJointWeights = getJointMeshData(jointContent, *rootJoint);
    auto materials = parseMaterials(materialContent);
    auto geometry = getGeometryData(geometryContent);
    auto shapes = createAnimatedShapes(meshJointWeights, materials, geometry);

    std::vector<Pose> poses;
    if (!keyframeContent.empty()) {
        poses = loadPoses(keyframeContent);
    }

    rootJoint->initWorldTransformation(Mat4());

    return new AnimatedModel(shapes, *rootJoint, poses);
}

std::string AnimatedModelLoader::getContent(const std::string &name, const std::string &content) {
    std::string startTag = "<" + name + ">";
    std::string endTag = "</" + name + ">";
    int startIndex = content.find(startTag);
    int endIndex = content.find(endTag);
    return content.substr(startIndex, endIndex - startIndex);
}

std::map<std::string, std::vector<AnimatedModelLoader::MeshJointWeights>>AnimatedModelLoader::getJointMeshData(const std::string &content, Joint& rootJoint) {
    std::vector<std::string> controllerContents = StringUtils::split(content, "</controller>");

    std::map<std::string, std::vector<MeshJointWeights>> meshJointWeights;

    for (auto & controllerContent : controllerContents) {
        if (StringUtils::trim(controllerContent).empty()) {
            continue;
        }

        std::string meshId = StringUtils::removePrefix(getString("<skin source", controllerContent), "#");
        std::string requiredJointsContent = getTagContent("source", 0, controllerContent);
        std::string inverseBindMatrixContent = getTagContent("source", 1, controllerContent);
        std::string weightContent = getTagContent("source", 2, controllerContent);
        std::string vertexWeightContent = getTagContent("vertex_weights", 0, controllerContent);
        std::vector<std::string> influencingJoints = getArray("<Name_array", requiredJointsContent);
        std::vector<float> inverseBindMatrices = getFloatArray("<float_array", inverseBindMatrixContent);

        transformationMatrix = Mat4(getFloatArray("<bind_shape_matrix>", controllerContent));

        for (int i = 0; i < influencingJoints.size(); i++) {
            Joint* requiredJoint;

            for (auto & joint : joints) {
                if (joint->getName() == influencingJoints[i]) {
                    requiredJoint = joint;
                }
            }

            std::vector<float> values = std::vector<float>(inverseBindMatrices.begin() + i * 16, inverseBindMatrices.begin() + (i + 1) * 16);
            Mat4 invBindMatrix(values);

            requiredJoint->setInverseBindMatrix(invBindMatrix);
        }

        std::vector<float> weights = getFloatArray("<float_array", weightContent);
        std::vector<int> weightsPerVertices = getIntArray("<vcount>", vertexWeightContent);
        std::vector<int> vertexJointWeights = getIntArray("<v>", vertexWeightContent);

        std::vector<MeshJointWeights> finalWeights;

        int counter = 0;
        for (int weightsPerVertex : weightsPerVertices) {
            Vec4 jointIndices;
            Vec4 jointWeights;

            for (int j = counter; j < counter + weightsPerVertex; j++) {
                if (j - counter >= 4) {
                    continue;
                }

                int localJointIndex = vertexJointWeights[j * 2];
                std::string jointName = influencingJoints[localJointIndex];

                int jointIndex = 0;
                for (auto & joint : joints) {
                    if (joint->getName() == jointName) {
                        jointIndex = joint->getId();
                    }
                }

                jointIndices[j - counter] = (float)jointIndex;

                int weightIndex = vertexJointWeights[j * 2 + 1];
                float weight = weights[weightIndex];
                jointWeights[j - counter] = weight;
            }
            counter += weightsPerVertex;
            finalWeights.emplace_back(MeshJointWeights(jointIndices, scaleVector(jointWeights)));
        }
        meshJointWeights[meshId] = finalWeights;
    }
    return meshJointWeights;
}

std::vector<Shape*> AnimatedModelLoader::createAnimatedShapes(std::map<std::string, std::vector<MeshJointWeights>> &meshJointWeights,
                                          std::map<std::string, Material> &materials,
                                          std::map<std::string, std::vector<GeometryData>> &geometries) {
    std::vector<Shape*> shapes;

    for (auto & geometry : geometries) {
        for (auto & shapeData : geometry.second) {
            Material material = materials[shapeData.materialId];
            Mesh * mesh = createGeometry(shapeData, meshJointWeights[geometry.first]);

            shapes.emplace_back(new Shape(*mesh, material));
        }
    }

    return shapes;
}

Joint * AnimatedModelLoader::getJointHierarchy(const std::string &content) {
    std::vector<std::string> lines = StringUtils::split(content, "\n");
    return getBoneData(lines, 0).first;
}

std::pair<Joint*, int> AnimatedModelLoader::getBoneData(const std::vector<std::string> &lines, int index) {
    int jointId = currentBoneIndex++;
    int i = index;
    std::string name;
    Mat4 localJointTransformation;
    std::vector<Joint *> children;

    while (true) {
        std::string line = StringUtils::trim(lines[i]);

        if (StringUtils::startsWith(line, "<node id")) {
            std::string type = getString("type", line);
            if (type == "JOINT") {
                if (!name.empty()) {
                    if (getString("name", line) == name) {
                        i++;
                        continue;
                    } else {
                        std::pair<Joint*, int> result = getBoneData(lines, i);
                        children.emplace_back(result.first);
                        i = result.second;
                    }
                } else {
                    name = getString("sid", line);
                    std::string bindMatrixLine = StringUtils::trim(lines[i + 1]);
                    localJointTransformation = Mat4(getFloatArray("transform", bindMatrixLine));
                }
            } else if (type == "NODE") {
                int j = i;
                while (true) {
                    std::string nextLine = StringUtils::trim(lines[j++]);
                    if (StringUtils::startsWith(nextLine, "<scale")) {
                        std::vector<float> values = getFloatArray("sid", nextLine);
                        scale.x = values[0];
                        scale.y = values[1];
                        scale.z = values[2];
                        break;
                    }
                }
                i++;
            }
        } else if (line.find("</node>") != std::string::npos) {
            if (jointId == 0) {
                localJointTransformation = rotationMatrix * localJointTransformation;
                localJointTransformation = localJointTransformation.scale(scale);
                localJointTransformation.scalePosition(scale);
            }

            auto * jointData = new Joint(name, jointId, children, localJointTransformation);
            joints.emplace_back(jointData);
            return std::pair(jointData, i);
        }
        i++;
    }
}

std::map<std::string, std::vector<AnimatedModelLoader::GeometryData>> AnimatedModelLoader::getGeometryData(const std::string &content) {
    std::map<std::string, std::vector<GeometryData>> geometries;
    std::vector<std::string> geometryContents = StringUtils::split(content, "</geometry>");

    for (auto & geometryContent : geometryContents) {
        if (StringUtils::trim(geometryContent).empty()) {
            continue;
        }

        std::string id = getId(geometryContent);
        int shapesStartIndex = geometryContent.find("<triangles");

        std::vector<std::string> shapeContents = StringUtils::split(geometryContent.substr(shapesStartIndex), "</triangles>");
        std::vector<GeometryData> shapes;

        for (auto & shapeContent : shapeContents) {
            if (!StringUtils::startsWith(StringUtils::trim(shapeContent), "<triangles")) {
                continue;
            }

            std::vector<AttributeData> attributes;
            std::vector<std::string> shapeLines = StringUtils::split(shapeContent, "\n");
            for (auto & line : shapeLines) {
                if (StringUtils::startsWith(StringUtils::trim(line), "<input semantic")) {
                    std::string attributeName = getString("input semantic", line);
                    int offset = std::stoi(getString("offset", line));
                    attributes.emplace_back(AttributeData(attributeName, offset));
                }
            }

            std::string materialId = getString("<triangles material", shapeContent);

            std::vector<float> positions = getFloatArray(id + "-positions-array", geometryContent);
            std::vector<float> normalValues = getFloatArray(id + "-normals-array", geometryContent);
            std::vector<float> texturesValues;

            try {
                getFloatArray(id + "-map-0-array", geometryContent);
            } catch (...) {

            }

            std::vector<int> indices = getIntArray("<p>", shapeContent);

            std::vector<Vec3> vertices;
            std::vector<Vec3> normals;
            std::vector<Vec2> textureCoordinates;

            for (int i = 0; i < positions.size(); i += 3) {
                vertices.emplace_back(positions[i], positions[i + 1], positions[i + 2]);
            }

            for (int i = 0; i < normalValues.size(); i += 3) {
                normals.emplace_back(normalValues[i], normalValues[i + 1], normalValues[i + 2]);
            }

            for (int i = 0; i < texturesValues.size(); i += 2) {
                textureCoordinates.emplace_back(texturesValues[i], texturesValues[i + 1]);
            }

            shapes.emplace_back(GeometryData(materialId, vertices, normals, textureCoordinates, indices, attributes));
        }

        geometries[id] = shapes;
    }

    return geometries;
}

Mesh * AnimatedModelLoader::createGeometry(AnimatedModelLoader::GeometryData &geometryData,
                                         const std::vector<MeshJointWeights> &meshJointWeights) {

    std::vector<GLuint> indices;
    bool containsTextureCoordinates = false;
    if (std::any_of(geometryData.attributes.begin(), geometryData.attributes.end(), [](AnimatedModelLoader::AttributeData & attribute) {
        return attribute.name == "TEXCOORD";
    })) {
        containsTextureCoordinates = true;
    }

    int stepSize = geometryData.attributes.size();

    int positionOffset = 0;
    for (auto & attribute : geometryData.attributes) {
        if (attribute.name == "VERTEX") {
            positionOffset = attribute.offset;
            break;
        }
    }

    int normalOffset = 0;
    for (auto & attribute : geometryData.attributes) {
        if (attribute.name == "NORMAL") {
            normalOffset = attribute.offset;
            break;
        }
    }

    int texCoordOffset = -1;
    if (containsTextureCoordinates) {
        for (auto & attribute : geometryData.attributes) {
            if (attribute.name == "TEXCOORD") {
                texCoordOffset = attribute.offset;
                break;
            }
        }
    }

    std::vector<Attribute> attributes = {
            Attribute(0, 3),
            Attribute(1, 3),
            Attribute(3, 4),
            Attribute(4, 4, Attribute::FLOAT)
    };

    if (containsTextureCoordinates) {
        attributes.emplace_back(Attribute(2, 2));
    }

    Layout layout(attributes);

    char buffer[geometryData.indexData.size() * stepSize * 14];
    int j = 0;

    FloatBuffer floatBuffer = {};
    IntBuffer intBuffer = {};

    for (int i = 0; i < geometryData.indexData.size(); i += stepSize) {
        int positionIndex = geometryData.indexData[i + positionOffset];
        int normalIndex = geometryData.indexData[i + normalOffset];

        Vec4 position = transformationMatrix * (geometryData.positions[positionIndex]);
        Vec4 normal = transformationMatrix * (geometryData.normals[normalIndex]);

        floatBuffer.value = position.x;
        buffer[j++] = floatBuffer.data[0];
        buffer[j++] = floatBuffer.data[1];
        buffer[j++] = floatBuffer.data[2];
        buffer[j++] = floatBuffer.data[3];

        floatBuffer.value = position.y;
        buffer[j++] = floatBuffer.data[0];
        buffer[j++] = floatBuffer.data[1];
        buffer[j++] = floatBuffer.data[2];
        buffer[j++] = floatBuffer.data[3];

        floatBuffer.value = position.z;
        buffer[j++] = floatBuffer.data[0];
        buffer[j++] = floatBuffer.data[1];
        buffer[j++] = floatBuffer.data[2];
        buffer[j++] = floatBuffer.data[3];

        floatBuffer.value = normal.x;
        buffer[j++] = floatBuffer.data[0];
        buffer[j++] = floatBuffer.data[1];
        buffer[j++] = floatBuffer.data[2];
        buffer[j++] = floatBuffer.data[3];

        floatBuffer.value = normal.y;
        buffer[j++] = floatBuffer.data[0];
        buffer[j++] = floatBuffer.data[1];
        buffer[j++] = floatBuffer.data[2];
        buffer[j++] = floatBuffer.data[3];

        floatBuffer.value = normal.z;
        buffer[j++] = floatBuffer.data[0];
        buffer[j++] = floatBuffer.data[1];
        buffer[j++] = floatBuffer.data[2];
        buffer[j++] = floatBuffer.data[3];

        if (containsTextureCoordinates) {
            Vec2 textureCoordinate = geometryData.textureCoordinates[geometryData.indexData[i + texCoordOffset]];
            floatBuffer.value = textureCoordinate.x;
            buffer[j++] = floatBuffer.data[0];
            buffer[j++] = floatBuffer.data[1];
            buffer[j++] = floatBuffer.data[2];
            buffer[j++] = floatBuffer.data[3];

            floatBuffer.value = textureCoordinate.y;
            buffer[j++] = floatBuffer.data[0];
            buffer[j++] = floatBuffer.data[1];
            buffer[j++] = floatBuffer.data[2];
            buffer[j++] = floatBuffer.data[3];
        }

        Vec4 boneWeights = meshJointWeights[positionIndex].jointWeights;

        floatBuffer.value = boneWeights[0];
        buffer[j++] = floatBuffer.data[0];
        buffer[j++] = floatBuffer.data[1];
        buffer[j++] = floatBuffer.data[2];
        buffer[j++] = floatBuffer.data[3];

        floatBuffer.value = boneWeights[1];
        buffer[j++] = floatBuffer.data[0];
        buffer[j++] = floatBuffer.data[1];
        buffer[j++] = floatBuffer.data[2];
        buffer[j++] = floatBuffer.data[3];

        floatBuffer.value = boneWeights[2];
        buffer[j++] = floatBuffer.data[0];
        buffer[j++] = floatBuffer.data[1];
        buffer[j++] = floatBuffer.data[2];
        buffer[j++] = floatBuffer.data[3];

        floatBuffer.value = boneWeights[3];
        buffer[j++] = floatBuffer.data[0];
        buffer[j++] = floatBuffer.data[1];
        buffer[j++] = floatBuffer.data[2];
        buffer[j++] = floatBuffer.data[3];

        Vec4 boneIds = meshJointWeights[positionIndex].jointIds;
//        floatBuffer.value = boneIds[0];
//        buffer[j++] = floatBuffer.data[0];
//        buffer[j++] = floatBuffer.data[1];
//        buffer[j++] = floatBuffer.data[2];
//        buffer[j++] = floatBuffer.data[3];
//
//        floatBuffer.value = boneIds[1];
//        buffer[j++] = floatBuffer.data[0];
//        buffer[j++] = floatBuffer.data[1];
//        buffer[j++] = floatBuffer.data[2];
//        buffer[j++] = floatBuffer.data[3];
//
//        floatBuffer.value = boneIds[2];
//        buffer[j++] = floatBuffer.data[0];
//        buffer[j++] = floatBuffer.data[1];
//        buffer[j++] = floatBuffer.data[2];
//        buffer[j++] = floatBuffer.data[3];
//
//        floatBuffer.value = boneIds[3];
//        buffer[j++] = floatBuffer.data[0];
//        buffer[j++] = floatBuffer.data[1];
//        buffer[j++] = floatBuffer.data[2];
//        buffer[j++] = floatBuffer.data[3];

        intBuffer.value = (int)boneIds[0];
        buffer[j++] = intBuffer.data[0];
        buffer[j++] = intBuffer.data[1];
        buffer[j++] = intBuffer.data[2];
        buffer[j++] = intBuffer.data[3];

        intBuffer.value = (int)boneIds[1];
        buffer[j++] = intBuffer.data[0];
        buffer[j++] = intBuffer.data[1];
        buffer[j++] = intBuffer.data[2];
        buffer[j++] = intBuffer.data[3];

        intBuffer.value = (int)boneIds[2];
        buffer[j++] = intBuffer.data[0];
        buffer[j++] = intBuffer.data[1];
        buffer[j++] = intBuffer.data[2];
        buffer[j++] = intBuffer.data[3];

        intBuffer.value = (int)boneIds[3];
        buffer[j++] = intBuffer.data[0];
        buffer[j++] = intBuffer.data[1];
        buffer[j++] = intBuffer.data[2];
        buffer[j++] = intBuffer.data[3];

        indices.emplace_back(indices.size());
    }

    return new Mesh(layout, buffer, indices);
}

std::vector<Pose> AnimatedModelLoader::loadPoses(const std::string &content) {
    std::vector<std::string> animationContents = StringUtils::split(content, "</animation>");

    std::vector<Pose> poses;
    std::vector<std::map<std::string, JointTransformation>> poseTransformations;

    for (auto & animationContent : animationContents) {
        if (StringUtils::trim(animationContent).empty()) {
            continue;
        }

        std::string id = StringUtils::removeSuffix(StringUtils::removePrefix(getString("<animation id", animationContent), "Armature_"), "_pose_matrix");
        std::string jointId;
        std::string rootJointName;

        for (auto & joint : joints) {
            if (joint->getId() == 0) {
                rootJointName = joint->getName();
            }
            if (id == joint->getName()) {
                jointId = joint->getName();
            }
        }

        std::string poseContent = getTagContent("source", 1, animationContent);
        std::vector<float> poseData = getFloatArray("<float_array", poseContent);

        int numberOfMatrices = (int)poseData.size() / 16;

        if (poseTransformations.size() != numberOfMatrices) {
            for (int i = 0; i < numberOfMatrices; i++) {
                poseTransformations.emplace_back(std::map<std::string, JointTransformation>());
            }
        }

        for (int i = 0; i < numberOfMatrices; i++) {
            Mat4 poseMatrix(std::vector<float>(poseData.begin() + i * 16, poseData.begin() + (i + 1) * 16));

            if (jointId == rootJointName) {
                poseMatrix = (rotationMatrix * poseMatrix).scalePosition(scale);
                JointTransformation jointTransformation(poseMatrix.getPosition(), poseMatrix.toQuaternion(), scale);
                poseTransformations[i][jointId] = jointTransformation;
            } else {
                JointTransformation jointTransformation(poseMatrix.getPosition(), poseMatrix.toQuaternion());
                poseTransformations[i][jointId] = jointTransformation;
            }
        }
    }

    poses.reserve(poseTransformations.size());
    for (auto & jointTransforms : poseTransformations) {
        poses.emplace_back(jointTransforms);
    }

    return poses;
}

std::map<std::string, Material> AnimatedModelLoader::parseMaterials(const std::string &content) {
    std::map<std::string, Material> materials;

    std::vector<std::string> materialContents = StringUtils::split(content, "</effect>");

    for (auto & materialContent : materialContents) {
        if (StringUtils::trim(materialContent).empty()) {
            continue;
        }

        std::string id = StringUtils::removeSuffix(getId(materialContent), "-effect") + "-material";
        Color diffuse = getColor("diffuse", materialContent);
        Color specular = getColor("specular", materialContent);

        float shininess = 0.0f;

        try {
            shininess = getFloatValue("shininess", materialContent);
        } catch (...) {

        }

        Material material(diffuse, specular, shininess);
        materials[id] = material;
    }

    return materials;
}

std::string AnimatedModelLoader::getId(const std::string &content) {
    int startIndex = (int)content.find("id=") + 4;
    int endIndex = (int)content.find('\"', startIndex);
    return content.substr(startIndex, endIndex - startIndex);
}

float AnimatedModelLoader::getFloatValue(const std::string &name, const std::string &content) {
    int nameIndex = content.find("\"" + name + "\"");
    if (nameIndex == -1) {
        throw std::runtime_error("No value was found for parameter " + name);
    }

    int startIndex = (int)content.find('>', nameIndex + name.length()) + 1;
    int endIndex = (int)content.find('<', startIndex + 1);
    return std::stof(content.substr(startIndex, endIndex - startIndex));
}

Color AnimatedModelLoader::getColor(const std::string &name, const std::string &content) {
    std::vector<float> values;
    try {
        values = getFloatArray("<color sid=\"" + name + "\">", content);
    } catch (...) {
        values = {
                0.0f, 0.0f, 0.0f, 0.0f
        };
    }

    if (values.size() != 4) {
        throw std::runtime_error("Invalid color: " + name);
    }

    return Color(values[0], values[1], values[2], values[3]);
}

std::vector<std::string> AnimatedModelLoader::getArray(const std::string &name, const std::string &content) {
    int nameIndex = (int)content.find(name);
    if (nameIndex == -1) {
        throw std::runtime_error("No array found with name: " + name);
    }

    int startIndex = (int)content.find('>', nameIndex) + 1;
    int endIndex = (int)content.find('<', startIndex + 1);

    return StringUtils::split(StringUtils::trim(content.substr(startIndex, endIndex - startIndex)), " ");
}

std::string AnimatedModelLoader::getString(const std::string &name, const std::string &content) {
    int nameIndex = content.find(name);
    if (nameIndex == -1) {
        throw std::runtime_error("No attribute found with name: " + name + " in content: " + content);
    }

    int startIndex = (int)content.find('\"', nameIndex) + 1;
    int endIndex = (int)content.find('\"', startIndex);

    return content.substr(startIndex, endIndex - startIndex);
}

std::string AnimatedModelLoader::getTagContent(const std::string &tagName, int occurrence, const std::string &content,
                                               bool isOneLine) {

    int searchIndex = 0;
    int timesFound = 0;

    while (true) {
        int startIndex = (int)content.find("<" + tagName, searchIndex) + 1;
        int endIndex = (int)content.find("</" + tagName + ">", startIndex);

        if (isOneLine) {
            endIndex = (int)content.find("/>", startIndex);
        }

        if (timesFound == occurrence) {
            return content.substr(startIndex, endIndex - startIndex);
        } else {
            timesFound++;
            searchIndex = endIndex;
        }
    }
}

std::string AnimatedModelLoader::getTagContent(const std::string &tagName, int occurrence, const std::string &content) {
    return getTagContent(tagName, occurrence, content, false);
}

std::vector<float> AnimatedModelLoader::getFloatArray(const std::string &name, const std::string &content) {
    std::vector<std::string> stringValues = getArray(name, content);
    std::vector<float> values;

    values.reserve(stringValues.size());
    for (auto & value : stringValues) {
        values.emplace_back(std::stof(StringUtils::trim(value)));
    }
    return values;
}

std::vector<int> AnimatedModelLoader::getIntArray(const std::string &name, const std::string &content) {
    std::vector<std::string> stringValues = getArray(name, content);
    std::vector<int> values;
    values.reserve(stringValues.size());
    for (auto & value : stringValues) {
        values.emplace_back(std::stoi(value));
    }
    return values;
}

Vec4 AnimatedModelLoader::scaleVector(Vec4 &weights) {
    float sum = weights.x + weights.y + weights.z + weights.w;
    return Vec4(weights.x / sum, weights.y / sum, weights.z / sum, weights.w / sum);
}
