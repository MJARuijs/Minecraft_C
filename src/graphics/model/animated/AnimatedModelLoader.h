#pragma once

#include <string>
#include <utility>
#include <vector>
#include <map>
#include "../../../math/vectors/Vec3.h"
#include "../../../math/vectors/Vec2.h"
#include "../../../math/vectors/Vec4.h"
#include "Joint.h"
#include "../Shape.h"
#include "animation/Pose.h"
#include "AnimatedModel.h"

class AnimatedModelLoader {

    union FloatBuffer {
        float value;
        char data[sizeof(float)];
    };

    union IntBuffer {
        int value;
        char data[sizeof(int)];
    };

private:

    struct AttributeData {
        std::string name;
        int offset;

        AttributeData(std::string name, int offset) : name(std::move(name)), offset(offset) {}
    };

    struct GeometryData {
        std::string materialId;
        std::vector<Vec3> positions;
        std::vector<Vec3> normals;
        std::vector<Vec2> textureCoordinates;
        std::vector<int> indexData;
        std::vector<AnimatedModelLoader::AttributeData> attributes;

        GeometryData(std::string materialId, std::vector<Vec3> positions, std::vector<Vec3> normals, std::vector<Vec2> textureCoordinates, std::vector<int> indexData, std::vector<AttributeData> attributes) : materialId(std::move(materialId)), positions(std::move(positions)), normals(std::move(normals)), textureCoordinates(std::move(textureCoordinates)), indexData(std::move(indexData)), attributes(std::move(attributes)) {}
    };

    struct MeshJointWeights {
        Vec4 jointIds;
        Vec4 jointWeights;

        MeshJointWeights(Vec4 jointIds, Vec4 jointWeights) : jointIds(jointIds), jointWeights(jointWeights) {}
    };

    int currentBoneIndex;
    std::vector<Joint*> joints;
    Mat4 rotationMatrix;
    Mat4 transformationMatrix;
    Vec3 scale;

    static std::string getContent(const std::string & name, const std::string & content);

    std::map<std::string, std::vector<MeshJointWeights>> getJointMeshData(const std::string & content, Joint& rootJoint);

    std::vector<Shape*> createAnimatedShapes(std::map<std::string, std::vector<MeshJointWeights>> & meshJointWeights, std::map<std::string, Material>& materials, std::map<std::string, std::vector<GeometryData>> & geometries);

    Joint * getJointHierarchy(const std::string & content);

    std::pair<Joint*, int> getBoneData(const std::vector<std::string> & lines, int index);

    static std::map<std::string, std::vector<GeometryData>> getGeometryData(const std::string & content);

    Mesh * createGeometry(GeometryData & geometryData, const std::vector<MeshJointWeights> & meshJointWeights);

    std::vector<Pose> loadPoses(const std::string & content);

    static std::map<std::string, Material> parseMaterials(const std::string & content);

    static std::string getId(const std::string & content);

    static float getFloatValue(const std::string & name, const std::string & content);

    static Color getColor(const std::string & name, const std::string & content);

    static std::string getString(const std::string & name, const std::string & content);

    static std::string getTagContent(const std::string & tagName, int occurrence, const std::string & content, bool isOneLine);
    static std::string getTagContent(const std::string & tagName, int occurrence, const std::string & content);

    static std::vector<std::string> getArray(const std::string & name, const std::string & content);
    static std::vector<float> getFloatArray(const std::string & name, const std::string & content);
    static std::vector<int> getIntArray(const std::string & name, const std::string & content);

    static Vec4 scaleVector(Vec4 & weights);

public:
    AnimatedModelLoader();
    AnimatedModel * load(const std::string & path);
};