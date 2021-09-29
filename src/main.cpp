#include "graphics/GraphicsContext.h"
#include "devices/GLFW.h"
#include "devices/Devices.h"
#include "math/matrices/Mat4.h"
#include "game/Camera.h"
#include "game/player/controller/FreeController.h"
#include "graphics/model/static/StaticModelLoader.h"
#include "graphics/entity/EntityRenderer.h"
#include "environment/sky/Skybox.h"
#include "environment/terrain/chunks/ChunkManager.h"
#include "environment/terrain/chunks/ChunkRenderer.h"
#include "graphics/model/animated/AnimatedModel.h"
#include "graphics/model/animated/AnimatedModelCache.h"
#include "graphics/entity/StaticEntity.h"
#include "graphics/entity/AnimatedEntity.h"
#include "graphics/rendertarget/RenderTargetManager.h"
#include "graphics/renderer/RenderEngine.h"
#include "graphics/model/static/StaticModelCache.h"
#include "environment/terrain/Selector.h"

int main() {
    GLFW glfw;
    Devices devices;
    GraphicsContext::init(Color(0.25f, 0.25f, 0.25f));

    GraphicsContext::enable(GraphicsContext::DEPTH_TESTING);
    GraphicsContext::enable(GraphicsContext::FACE_CULLING);
    GraphicsContext::enable(GraphicsContext::MULTI_SAMPLE);
    GraphicsContext::enable(GraphicsContext::TEXTURE_MAPPING);

    RenderTargetManager::init(devices.window.getWidth(), devices.window.getHeight());

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    UIPage page("page");
//    Item crossHair("crossHair", ConstraintSet(
//            new CenterConstraint(HORIZONTAL),
//            new CenterConstraint(VERTICAL),
//            new RelativeConstraint(VERTICAL, 0.05f),
//            new AspectRatioConstraint(HORIZONTAL, 1.0f)
//    ), new TexturedBackground("res/textures/userinterface/crosshair.jpg"));

//    crossHair.draw();
    Camera camera(devices.window.getAspectRatio());

    AmbientLight ambient(Color(0.75f, 0.75f, 0.75f));
    Sun sun(Color(0.5f, 0.5f, 0.5f), Vec3(1.0f, 1.0f, -1.0f));
    Skybox skybox("res/textures/sky/box", camera.getFarPlane());

    FreeController controller(Vec3(0.0f, 17.0f, 0.0f));

    RenderEngine renderEngine(true);

    ChunkManager chunkManager(0, 0);
    auto * chunkRenderer = new ChunkRenderer();
    auto * entityRenderer = new EntityRenderer();

    Selector selector;
    std::pair<Vec3, Face::FaceDirection> selectedBlock;

    std::vector<Renderable*> chunks;
    std::vector<Renderable*> entities;

    StaticModel* model = StaticModelCache::get("res/models/box.dae");
    StaticEntity box(model, Mat4().setPosition(Vec3(0, -20, 0)));
//    entities.emplace_back(&box);
    AnimatedModel * animatedModel = AnimatedModelCache::get("res/models/player3.dae");
    AnimatedEntity player(animatedModel, Mat4().setPosition(Vec3(0, 17, 0)));

//    entities.emplace_back(&player);

    animatedModel->addAnimation("walking", {
            std::pair(4, 400),
            std::pair(5, 400)
    }, LoopEffect::REVERSING);

    devices.mouse().capture();
    devices.showWindow();

    ShaderProgram boneProgram("res/shaders/debug/bone.vert", "res/shaders/debug/bone.frag");

    while (!devices.window.isClosed()) {
        glfw.poll();

        if (devices.keyboard().keyPressed(GLFW_KEY_ESCAPE)) {
            devices.mouse().toggle();
        }

        if (devices.keyboard().keyPressed(GLFW_KEY_F1)) {
            devices.window.close();
        }

        if (devices.keyboard().keyPressed(GLFW_KEY_UP)) {
            chunkManager.setRenderDistance(chunkManager.getRenderDistance() + 1);
        }

        if (devices.keyboard().keyPressed(GLFW_KEY_DOWN)) {
            chunkManager.setRenderDistance(chunkManager.getRenderDistance() - 1);
        }

        if (devices.mouse().captured) {
            if (devices.mouse().isButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
                bool blockSelected = Selector::getSelected(chunks, camera, camera.getPosition(), selectedBlock);
                if (blockSelected) {
                    for (auto & chunk : chunks) {
                        if (reinterpret_cast<Chunk*>(chunk)->containsBlock(selectedBlock.first)) {
                            reinterpret_cast<Chunk*>(chunk)->removeBlock(selectedBlock.first);
                        }
                    }
                }
            }

            if (devices.mouse().isButtonPressed(GLFW_MOUSE_BUTTON_RIGHT) || devices.keyboard().keyPressed(GLFW_KEY_V)) {
                bool blockSelected = Selector::getSelected(chunks, camera, camera.getPosition(), selectedBlock);
                if (blockSelected) {
                    for (auto & chunk : chunks) {
                        if (reinterpret_cast<Chunk*>(chunk)->containsBlock(selectedBlock.first)) {
                            reinterpret_cast<Chunk*>(chunk)->addBlock(selectedBlock.first + Face::getNormal(selectedBlock.second), BlockType::DIAMOND_ORE);
                        }
                    }
                }
            }
        }

        if (devices.keyboard().keyPressed(GLFW_KEY_RIGHT)) {
            player.animate("walking");
        }

        if (devices.mouse().captured) {
            controller.update(camera, devices.mouse(), devices.keyboard(), devices.timer.delta());
        }

        for (auto & entity : entities) {
            if (reinterpret_cast<Entity*>(entity)->getType() == Entity::ANIMATED) {
                reinterpret_cast<AnimatedEntity*>(entity)->update(devices.timer.delta());
            }
        }

        chunkManager.updatePosition(camera.getPosition());
        chunks = chunkManager.determineVisibleChunks();

        renderEngine.render(camera, ambient, sun, skybox, {
            RenderData(chunks, chunkRenderer, FORWARD),
            RenderData(entities, entityRenderer, FORWARD)
        });

        devices.update();
    }

    return 0;
}

void renderJoints() {
//        GraphicsContext::disable(GraphicsContext::FACE_CULLING);
//        boneProgram.start();
//        boneProgram.set("projection", camera.projectionMatrix);
//        boneProgram.set("view", camera.viewMatrix());
//
//        std::vector<Joint> joints = player.model->getJoints();
//        for (auto & joint : joints) {
//            joint.render(boneProgram);
//        }
//        GraphicsContext::enable(GraphicsContext::FACE_CULLING);

}
