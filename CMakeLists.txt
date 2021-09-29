cmake_minimum_required(VERSION 3.17)
project(Minecraft)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB_RECURSE SOURCE_FILES src/**.h src/**.cpp)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# Glew
find_package(GLEW REQUIRED)
include_directories(${PROJECT_SOURCE_DIR}/libraries/glew/include)

# stb
include_directories(${PROJECT_SOURCE_DIR}/libraries/stb/include)

# Assimp
include_directories(${PROJECT_SOURCE_DIR}/libraries/assimp/include)
link_directories(${PROJECT_SOURCE_DIR}/libraries/assimp/lib)

add_executable(Minecraft ${SOURCE_FILES} src/graphics/model/static/StaticModelCache.cpp src/graphics/model/static/StaticModelCache.h src/resources/images/ImageData.cpp src/resources/images/ImageData.h src/graphics/model/mesh/MeshLoader.cpp src/graphics/model/mesh/MeshLoader.h src/graphics/model/mesh/MeshCache.cpp src/graphics/model/mesh/MeshCache.h src/environment/terrain/chunks/Chunk.cpp src/environment/terrain/chunks/Chunk.h src/environment/terrain/chunks/ChunkGenerator.cpp src/environment/terrain/chunks/ChunkGenerator.h src/environment/terrain/chunks/ChunkManager.cpp src/environment/terrain/chunks/ChunkManager.h src/environment/terrain/chunks/ChunkRenderer.cpp src/environment/terrain/chunks/ChunkRenderer.h src/environment/terrain/chunks/ChunkMesh.cpp src/environment/terrain/chunks/ChunkMesh.h src/environment/terrain/blocks/BlockData.cpp src/environment/terrain/blocks/BlockData.h src/environment/terrain/blocks/FaceMaterial.cpp src/environment/terrain/blocks/FaceMaterial.h src/game/Tool.cpp src/game/Tool.h src/environment/terrain/chunks/Face.cpp src/environment/terrain/chunks/Face.h src/environment/terrain/FaceTextures.h src/graphics/textures/TextureArray.cpp src/graphics/textures/TextureArray.h src/environment/terrain/Biome.cpp src/environment/terrain/Biome.h src/environment/terrain/FaceTextures.cpp src/environment/terrain/blocks/BlockType.cpp src/environment/terrain/blocks/BlockType.h src/graphics/textures/TextureMapType.h src/graphics/model/animated/AnimatedModelLoader.cpp src/graphics/model/animated/AnimatedModelLoader.h src/graphics/model/animated/AnimatedModel.cpp src/graphics/model/animated/AnimatedModel.h src/graphics/model/animated/AnimatedModelCache.cpp src/graphics/model/animated/AnimatedModelCache.h src/graphics/model/animated/Joint.cpp src/graphics/model/animated/Joint.h src/graphics/model/animated/JointTransformation.cpp src/graphics/model/animated/JointTransformation.h src/math/Quaternion.cpp src/math/Quaternion.h src/graphics/model/animated/animation/Pose.cpp src/graphics/model/animated/animation/Pose.h src/graphics/model/animated/animation/Animation.cpp src/graphics/model/animated/animation/Animation.h src/graphics/model/animated/animation/Animator.cpp src/graphics/model/animated/animation/Animator.h src/graphics/model/animated/animation/KeyFrame.cpp src/graphics/model/animated/animation/KeyFrame.h src/graphics/entity/AnimatedEntity.cpp src/graphics/entity/AnimatedEntity.h src/graphics/entity/StaticEntity.cpp src/graphics/entity/StaticEntity.h src/graphics/model/animated/animation/LoopEffect.h src/graphics/rendertarget/RenderTarget.cpp src/graphics/rendertarget/RenderTarget.h src/graphics/rendertarget/attachments/Attachment.cpp src/graphics/rendertarget/attachments/Attachment.h src/graphics/rendertarget/attachments/ColorTextureAttachment.cpp src/graphics/rendertarget/attachments/ColorTextureAttachment.h src/graphics/textures/ColorMap.cpp src/graphics/textures/ColorMap.h src/graphics/rendertarget/attachments/ColorBufferAttachment.cpp src/graphics/rendertarget/attachments/ColorBufferAttachment.h src/graphics/textures/DepthMap.cpp src/graphics/textures/DepthMap.h src/graphics/rendertarget/RenderTargetManager.cpp src/graphics/rendertarget/RenderTargetManager.h src/graphics/renderer/RenderEngine.cpp src/graphics/renderer/RenderEngine.h src/graphics/renderer/ForwardRenderEngine.cpp src/graphics/renderer/ForwardRenderEngine.h src/graphics/renderer/DeferredRenderEngine.cpp src/graphics/renderer/DeferredRenderEngine.h src/graphics/renderer/Renderable.cpp src/graphics/renderer/Renderable.h src/graphics/renderer/Renderer.cpp src/graphics/renderer/Renderer.h src/graphics/renderer/RenderData.cpp src/graphics/renderer/RenderData.h src/graphics/renderer/RenderType.h src/math/SimplexNoise.cpp src/math/SimplexNoise.h src/math/Noise.cpp src/math/Noise.h src/environment/terrain/Selector.cpp src/environment/terrain/Selector.h src/util/FloatUtils.h)

target_link_libraries(${PROJECT_NAME} glfw GL GLU Xxf86vm Xrandr Xi X11 dl pthread Xinerama Xcursor assimp ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
