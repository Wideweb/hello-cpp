#include "RenderSystem.hpp"
#include "Application.hpp"
#include "LocationComponent.hpp"
#include "RenderComponent.hpp"
#include "cmath"

namespace Engine {

void RenderSystem::exec(std::vector<std::shared_ptr<Entity>> &entities) {
    auto &render = Application::get().getRender();
    auto &window = Application::get().getWindow();
    auto &camera = Application::get().getCamera();

    float windowWidth = static_cast<float>(window.getWidth());
    float windowHeight = static_cast<float>(window.getHeight());

    for (auto entity : entities) {
        if (entity->hasComponent<RenderComponent>()) {
            auto c_render = entity->getComponent<RenderComponent>();
            auto c_location = entity->getComponent<LocationComponent>();

            float x = (c_location->x - camera.x) / windowWidth * 2.0 - 1;
            float y = (c_location->y - camera.y) / windowHeight * 2.0 - 1;
            float anlge = c_location->angleRad;
            float cos = std::cos(anlge);
            float sin = std::sin(anlge);
            float tx = x * cos + y * sin;
            float ty = y * cos - x * sin;

            float scaleX = c_render->width / windowWidth;
            float scaleY = c_render->height / windowHeight;

            std::vector<float> model = {scaleX, 0.0f,   0.0f, 0.0f,

                                        0.0f,   scaleY, 0.0f, 0.0f,

                                        0.0f,   0.0f,   1.0f, 0.0f,

                                        x,      y,      0.0f, 1.0f};

            c_render->shader->SetMatrix4("MVP", model);
            render.drawTriangles(c_render->shader, c_render->vertexArray);
        }
    }
}

} // namespace Engine
