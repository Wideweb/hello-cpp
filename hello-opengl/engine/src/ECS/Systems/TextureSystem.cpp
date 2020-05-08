#include "TextureSystem.hpp"
#include "Application.hpp"
#include "LocationComponent.hpp"
#include "Math.hpp"
#include "TextureComponent.hpp"
#include "cmath"

namespace Engine {

void TextureSystem::exec(EntityManager &entities) {
    auto &render = Application::get().getRender();
    auto &window = Application::get().getWindow();
    auto &camera = Application::get().getCamera();
    auto &textures = Application::get().getTextures();

    float windowWidth = static_cast<float>(window.getWidth());
    float windowHeight = static_cast<float>(window.getHeight());

    for (auto entity : entities.getAll()) {
        if (entity->hasComponent<TextureComponent>()) {
            auto c_texture = entity->getComponent<TextureComponent>();
            auto c_location = entity->getComponent<LocationComponent>();

            float x = (c_location->x - camera.x) / windowWidth * 2.0 - 1;
            float y = (c_location->y - camera.y) / windowHeight * 2.0 - 1;

            float scaleX = c_texture->width / windowWidth;
            float scaleY = c_texture->height / windowHeight;

            Mat2x3 scale = Mat2x3::scale(scaleX, scaleY);
            Mat2x3 rotate = Mat2x3::rotate(0);
            Mat2x3 move = Mat2x3::move(Vec2(x, y));
            Mat2x3 model = move * rotate * scale;

            Mat2 textureModel = Mat2::identity();
            if (c_location->direction == Direction::Left) {
                textureModel = Mat2::flipY();
            }

            c_texture->shader->setMatrix2x3("model", model.data());
            c_texture->shader->setMatrix2("texture_model", textureModel.data());

            render.drawTexture(c_texture->shader, c_texture->vertexArray,
                               textures.get(c_texture->name));
        }
    }
}

} // namespace Engine
