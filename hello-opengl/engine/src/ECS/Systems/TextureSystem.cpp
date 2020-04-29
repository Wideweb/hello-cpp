#include "TextureSystem.hpp"
#include "Application.hpp"
#include "LocationComponent.hpp"
#include "TextureComponent.hpp"
#include "cmath"

namespace Engine {

void TextureSystem::exec(std::vector<std::shared_ptr<Entity>> &entities) {
    auto &render = Application::get().getRender();
    auto &window = Application::get().getWindow();
    auto &camera = Application::get().getCamera();

    float windowWidth = static_cast<float>(window.getWidth());
    float windowHeight = static_cast<float>(window.getHeight());

    for (auto entity : entities) {
        if (entity->hasComponent<TextureComponent>()) {
            auto c_texture = entity->getComponent<TextureComponent>();
            auto c_location = entity->getComponent<LocationComponent>();

            float x = (c_location->x - camera.x) / windowWidth * 2.0 - 1;
            float y = (c_location->y - camera.y) / windowHeight * 2.0 - 1;

            float scaleX = c_texture->width / windowWidth;
            float scaleY = c_texture->height / windowHeight;

            std::vector<float> model = {scaleX, 0.0f,   0.0f, 0.0f,

                                        0.0f,   scaleY, 0.0f, 0.0f,

                                        0.0f,   0.0f,   1.0f, 0.0f,

                                        x,      y,      0.0f, 1.0f};

            c_texture->shader->setMatrix4("MVP", model);
            render.drawTexture(c_texture->shader, c_texture->vertexArray,
                               c_texture->texture);
        }
    }
}

} // namespace Engine
