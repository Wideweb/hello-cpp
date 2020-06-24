#include "TextureSystem.hpp"
#include "Application.hpp"
#include "DirectionComponent.hpp"
#include "FrameAnimationComponent.hpp"
#include "FrameComponent.hpp"
#include "IgnoreLightComponent.hpp"
#include "LocationComponent.hpp"
#include "MaterialComponent.hpp"
#include "Math.hpp"
#include "ParalaxScrollingComponent.hpp"
#include "ParentComponent.hpp"
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

    auto entititesWithTexture = entities.getByComponent<TextureComponent>();

    for (auto entity : entititesWithTexture) {
        auto texture = entity->getComponent<TextureComponent>();
        auto material = entity->getComponent<MaterialComponent>();
        auto location = entity->getComponent<LocationComponent>();
        auto direction = entity->getComponent<DirectionComponent>();

        float paralaxScale = 1.0;
        float parentX = 0;
        float parentY = 0;

        if (entity->hasComponent<ParalaxScrollingComponent>()) {
            auto pralax = entity->getComponent<ParalaxScrollingComponent>();
            paralaxScale = pralax->scale;
        }

        if (entity->hasComponent<ParentComponent>()) {
            std::string parentId =
                entity->getComponent<ParentComponent>()->parent;
            auto parent = entities.get(parentId);
            auto parentLocation = parent->getComponent<LocationComponent>();

            parentX = parentLocation->x;
            parentY = parentLocation->y;
        }

        float x = (location->x + parentX - camera.x * paralaxScale) /
                      windowWidth * 2.0 -
                  1;
        float y = (location->y + parentY - camera.y * paralaxScale) /
                      windowHeight * 2.0 -
                  1;

        float scaleX = location->scale * texture->width / windowWidth;
        float scaleY = location->scale * texture->height / windowHeight;

        Mat2x3 scale = Mat2x3::scale(scaleX, scaleY);
        Mat2x3 rotate = Mat2x3::rotate(location->angle);
        Mat2x3 move = Mat2x3::move(Vec2(x, y));
        Mat2x3 model = move * scale * rotate;

        Mat2x3 textureModel = Mat2x3::identity();
        if (direction->x > 0) {
            textureModel = Mat2x3::flipY();
        }

        if (entity->hasComponent<FrameAnimationComponent>()) {
            auto animation = entity->getComponent<FrameAnimationComponent>();
            auto current = animation->getCurrent();

            float x = current.dx * animation->frameIndex;
            if (direction->x > 0) {
                x = x + current.dx;
            }

            float y = current.y;

            textureModel = Mat2x3::move(Vec2(x, y)) * textureModel;
        }

        if (entity->hasComponent<FrameComponent>()) {
            auto frame = entity->getComponent<FrameComponent>();

            float x = texture->source.w * frame->index;

            textureModel = Mat2x3::move(Vec2(x, 1.0)) * textureModel;
        }

        std::shared_ptr<Shader> shader;

        if (entity->hasComponent<IgnoreLightComponent>()) {
            shader = shaders.get("texture");
        } else {
            shader = shaders.get("texture-with-light");

            shader->setFloat3("material.ambient", material->ambient.x,
                              material->ambient.y, material->ambient.z);
            shader->setFloat3("material.diffuse", material->diffuse.x,
                              material->diffuse.y, material->diffuse.z);
            shader->setFloat3("material.specular", material->specular.x,
                              material->specular.y, material->specular.z);
            shader->setFloat("material.shininess", material->shininess);
        }

        shader->setMatrix2x3("model", model.data());
        shader->setMatrix2x3("texture_model", textureModel.data());
        shader->setFloat("alpha", texture->alpha);

        render.drawTexture(shader, texture->vertexArray,
                           textures.get(texture->name));
    }
}

} // namespace Engine
