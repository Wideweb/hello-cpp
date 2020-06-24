#include "RenderSystem.hpp"
#include "Application.hpp"
#include "IgnoreLightComponent.hpp"
#include "LocationComponent.hpp"
#include "MaterialComponent.hpp"
#include "ParalaxScrollingComponent.hpp"
#include "RenderComponent.hpp"
#include "cmath"

namespace Engine {

void RenderSystem::exec(EntityManager &entities) {
    auto &render = Application::get().getRender();
    auto &window = Application::get().getWindow();
    auto &camera = Application::get().getCamera();
    auto &shaders = Application::get().getShaders();

    float windowWidth = static_cast<float>(window.getWidth());
    float windowHeight = static_cast<float>(window.getHeight());

    for (auto entity : entities.getAll()) {
        if (entity->hasComponent<RenderComponent>()) {
            auto c_render = entity->getComponent<RenderComponent>();
            auto c_location = entity->getComponent<LocationComponent>();
            auto c_material = entity->getComponent<MaterialComponent>();

            float paralaxScale = 1.0;

            if (entity->hasComponent<ParalaxScrollingComponent>()) {
                auto pralax = entity->getComponent<ParalaxScrollingComponent>();
                paralaxScale = pralax->scale;
            }

            float dx = c_location->x - camera.x * paralaxScale;
            float dy = c_location->y - camera.y * paralaxScale;

            float x = dx / windowWidth * 2.0 - 1;
            float y = dy / windowHeight * 2.0 - 1;

            float scaleX = c_render->width / windowWidth;
            float scaleY = c_render->height / windowHeight;

            Mat2x3 scale = Mat2x3::scale(scaleX, scaleY);
            Mat2x3 rotate = Mat2x3::rotate(c_location->angle);
            Mat2x3 move = Mat2x3::move(Vec2(x, y));
            Mat2x3 model = move * scale * rotate;

            std::shared_ptr<Shader> shader;

            if (entity->hasComponent<IgnoreLightComponent>()) {
                shader = shaders.get("plain");
            } else {
                shader = shaders.get("plain-with-light");

                shader->setFloat3("material.ambient", c_material->ambient.x,
                                  c_material->ambient.y, c_material->ambient.z);
                shader->setFloat3("material.diffuse", c_material->diffuse.x,
                                  c_material->diffuse.y, c_material->diffuse.z);
                shader->setFloat3("material.specular", c_material->specular.x,
                                  c_material->specular.y,
                                  c_material->specular.z);
                shader->setFloat("material.shininess", c_material->shininess);
            }

            shader->setMatrix2x3("model", model.data());
            render.drawTriangles(shader, c_render->vertexArray);
        }
    }
}

} // namespace Engine
