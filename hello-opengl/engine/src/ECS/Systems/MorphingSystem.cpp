#include "MorphingSystem.hpp"
#include "Application.hpp"
#include "LocationComponent.hpp"
#include "MorphingComponent.hpp"
#include "cmath"
#include "iostream"

namespace Engine {

void MorphingSystem::exec(EntityManager &entities) {
    auto &render = Application::get().getRender();
    auto &window = Application::get().getWindow();
    auto &camera = Application::get().getCamera();
    auto &time = Application::get().getTime();

    float windowWidth = static_cast<float>(window.getWidth());
    float windowHeight = static_cast<float>(window.getHeight());

    for (auto entity : entities.getAll()) {
        if (entity->hasComponent<MorphingComponent>()) {
            auto c_render = entity->getComponent<MorphingComponent>();
            auto c_location = entity->getComponent<LocationComponent>();

            float x = (c_location->x - camera.x) / windowWidth * 2.0 - 1;
            float y = (c_location->y - camera.y) / windowHeight * 2.0 - 1;

            float scaleX = c_render->width / windowWidth;
            float scaleY = c_render->height / windowHeight;

            std::vector<float> model = {scaleX, 0.0f,   0.0f, 0.0f,

                                        0.0f,   scaleY, 0.0f, 0.0f,

                                        0.0f,   0.0f,   1.0f, 0.0f,

                                        x,      y,      0.0f, 1.0f};

            c_render->shader->setFloat("time", time.getTotalSeconds());
            c_render->shader->setMatrix4("MVP", model);
            render.drawTriangles(c_render->shader, c_render->vertexArray);
        }
    }
}

} // namespace Engine
