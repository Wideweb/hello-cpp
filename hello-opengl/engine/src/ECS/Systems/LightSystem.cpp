#include "LightSystem.hpp"
#include "Application.hpp"
#include "FrameAnimationComponent.hpp"
#include "LocationComponent.hpp"
#include "MaterialComponent.hpp"
#include "Math.hpp"
#include "ParalaxScrollingComponent.hpp"
#include "PointLightComponent.hpp"
#include "TextureComponent.hpp"
#include "cmath"
#include <vector>

namespace Engine {

void LightSystem::exec(EntityManager &entities) {
    auto &render = Application::get().getRender();
    auto &window = Application::get().getWindow();
    auto &camera = Application::get().getCamera();
    auto &textures = Application::get().getTextures();
    auto &shaders = Application::get().getShaders();

    float windowWidth = static_cast<float>(window.getWidth());
    float windowHeight = static_cast<float>(window.getHeight());

    auto pointLights = entities.getByComponent<PointLightComponent>();
    if (pointLights.size() == 0) {
        return;
    }

    for (size_t i = 0; i < pointLights.size(); i++) {
        auto entity = pointLights[i];
        auto light = entity->getComponent<PointLightComponent>();
        auto location = entity->getComponent<LocationComponent>();

        float paralaxScale = 1.0;

        if (entity->hasComponent<ParalaxScrollingComponent>()) {
            auto pralax = entity->getComponent<ParalaxScrollingComponent>();
            paralaxScale = pralax->scale;
        }

        float x =
            (location->x - camera.x * paralaxScale) / windowWidth * 2.0 - 1;
        float y =
            (location->y - camera.y * paralaxScale) / windowHeight * 2.0 - 1;

        auto shader1 = shaders.get("texture-with-light");
        auto shader2 = shaders.get("plain-with-light");
        std::vector<std::shared_ptr<Shader>> lightShaders = {shader1, shader2};

        for (auto shader : lightShaders) {
            shader->setInt("pointLightsNumber", pointLights.size());

            auto iStr = std::to_string(i);
            shader->setFloat2("pointLights[" + iStr + "].position", x, y);
            shader->setFloat3("pointLights[" + iStr + "].ambient",
                              light->ambient.x, light->ambient.y,
                              light->ambient.z);
            shader->setFloat3("pointLights[" + iStr + "].diffuse",
                              light->diffuse.x, light->diffuse.y,
                              light->diffuse.z);
            shader->setFloat3("pointLights[" + iStr + "].specular",
                              light->specular.x, light->specular.y,
                              light->specular.z);
            shader->setFloat("pointLights[" + iStr + "].constant",
                             light->constant);
            shader->setFloat("pointLights[" + iStr + "].linear", light->linear);
            shader->setFloat("pointLights[" + iStr + "].quadratic",
                             light->quadratic);
        }
    }
}

} // namespace Engine
