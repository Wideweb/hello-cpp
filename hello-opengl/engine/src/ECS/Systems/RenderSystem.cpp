#include "RenderSystem.hpp"
#include "Application.hpp"
#include "LocationComponent.hpp"
#include "RenderComponent.hpp"
#include "cmath"

namespace Engine {

void RenderSystem::exec(EntityManager &entities) {
    auto &render = Application::get().getRender();
    auto &window = Application::get().getWindow();
    auto &camera = Application::get().getCamera();

    float windowWidth = static_cast<float>(window.getWidth());
    float windowHeight = static_cast<float>(window.getHeight());

    for (auto entity : entities.getAll()) {
        if (entity->hasComponent<RenderComponent>()) {
            auto c_render = entity->getComponent<RenderComponent>();
            auto c_location = entity->getComponent<LocationComponent>();

            float dx = c_location->x;
            float dy = c_location->y;

            if (!c_location->isStatic) {
                dx -= camera.x;
                dy -= camera.y;
            }

            float x = dx / windowWidth * 2.0 - 1;
            float y = dy / windowHeight * 2.0 - 1;

            float scaleX = c_render->width / windowWidth;
            float scaleY = c_render->height / windowHeight;

            std::vector<float> model = {scaleX, 0.0f,   0.0f, 0.0f,

                                        0.0f,   scaleY, 0.0f, 0.0f,

                                        0.0f,   0.0f,   1.0f, 0.0f,

                                        x,      y,      0.0f, 1.0f};

            c_render->shader->setMatrix4("MVP", model);
            render.drawTriangles(c_render->shader, c_render->vertexArray);
        }
    }
}

} // namespace Engine
