#include "TextureSystem.hpp"
#include "Application.hpp"
#include "FrameAnimationComponent.hpp"
#include "LocationComponent.hpp"
#include "MaterialComponent.hpp"
#include "Math.hpp"
#include "ParalaxScrollingComponent.hpp"
#include "TextureComponent.hpp"
#include "cmath"

namespace Engine {

void TextureSystem::exec(EntityManager &entities) {
    auto &render = Application::get().getRender();
    auto &window = Application::get().getWindow();
    auto &camera = Application::get().getCamera();
    auto &textures = Application::get().getTextures();
    auto &shaders = Application::get().getShaders();

    float windowWidth = static_cast<float>(window.getWidth());
    float windowHeight = static_cast<float>(window.getHeight());

    for (auto entity : entities.getAll()) {
        if (entity->hasComponent<TextureComponent>()) {
            auto texture = entity->getComponent<TextureComponent>();
            auto material = entity->getComponent<MaterialComponent>();
            auto location = entity->getComponent<LocationComponent>();

            float paralaxScale = 1.0;

            if (entity->hasComponent<ParalaxScrollingComponent>()) {
                auto pralax = entity->getComponent<ParalaxScrollingComponent>();
                paralaxScale = pralax->scale;
            }

            float x =
                (location->x - camera.x * paralaxScale) / windowWidth * 2.0 - 1;
            float y =
                (location->y - camera.y * paralaxScale) / windowHeight * 2.0 -
                1;

            float scaleX = location->scale * texture->width / windowWidth;
            float scaleY = location->scale * texture->height / windowHeight;

            Mat2x3 scale = Mat2x3::scale(scaleX, scaleY);
            Mat2x3 rotate = Mat2x3::rotate(location->angle);
            Mat2x3 move = Mat2x3::move(Vec2(x, y));
            Mat2x3 model = move * scale * rotate;

            Mat2x3 textureModel = Mat2x3::identity();
            if (texture->flip == Flip::Y) {
                textureModel = Mat2x3::flipY();
            }

            if (entity->hasComponent<FrameAnimationComponent>()) {
                auto animation =
                    entity->getComponent<FrameAnimationComponent>();
                auto current = animation->getCurrent();

                float x = current.dx * animation->frameIndex;
                if (texture->flip == Flip::Y) {
                    x = x + current.dx;
                }

                float y = current.y;

                textureModel = Mat2x3::move(Vec2(x, y)) * textureModel;
            }

            auto shader = shaders.get(texture->shader);

            shader->setMatrix2x3("model", model.data());
            shader->setMatrix2x3("texture_model", textureModel.data());

            shader->setFloat3("material.ambient", material->ambient.x,
                              material->ambient.y, material->ambient.z);
            shader->setFloat3("material.diffuse", material->diffuse.x,
                              material->diffuse.y, material->diffuse.z);
            shader->setFloat3("material.specular", material->specular.x,
                              material->specular.y, material->specular.z);
            shader->setFloat("material.shininess", material->shininess);

            render.drawTexture(shader, texture->vertexArray,
                               textures.get(texture->name));
        }
    }
}

} // namespace Engine
