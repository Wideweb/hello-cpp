#include "SpotLightSystem.hpp"
#include "Application.hpp"
#include "FrameAnimationComponent.hpp"
#include "LocationComponent.hpp"
#include "MaterialComponent.hpp"
#include "Math.hpp"
#include "ParalaxScrollingComponent.hpp"
#include "SpotLightComponent.hpp"
#include "TextureComponent.hpp"
#include "cmath"
#include <vector>

namespace Engine {

void SpotLightSystem::exec(EntityManager &entities) {
    auto &render = Application::get().getRender();
    auto &window = Application::get().getWindow();
    auto &camera = Application::get().getCamera();
    auto &textures = Application::get().getTextures();

    float windowWidth = static_cast<float>(window.getWidth());
    float windowHeight = static_cast<float>(window.getHeight());

    auto lights = entities.getByComponent<SpotLightComponent>();

    auto shader1 = Application::get().getShaders().get("texture");
    auto shader2 = Application::get().getShaders().get("plain");
    std::vector<std::shared_ptr<Shader>> shaders = {shader1, shader2};

    for (auto shader : shaders) {
        shader->setInt("spotLightsNumber", lights.size());
    }

    if (lights.size() == 0) {
        return;
    }

    for (size_t i = 0; i < lights.size(); i++) {
        auto entity = lights[i];
        auto light = entity->getComponent<SpotLightComponent>();
        auto location = entity->getComponent<LocationComponent>();

        float x = (location->x - camera.x) / windowWidth * 2.0 - 1;
        float y = (location->y - camera.y) / windowHeight * 2.0 - 1;

        for (auto shader : shaders) {
            auto iStr = std::to_string(i);
            shader->setFloat2("spotLights[" + iStr + "].position", x, y);
            shader->setFloat2("spotLights[" + iStr + "].direction",
                              light->direction.x, light->direction.y);
            shader->setFloat("spotLights[" + iStr + "].cutOff", light->cutOff);
            shader->setFloat("spotLights[" + iStr + "].outerCutOff",
                             light->outerCutOff);
            shader->setFloat3("spotLights[" + iStr + "].ambient",
                              light->ambient.x, light->ambient.y,
                              light->ambient.z);
            shader->setFloat3("spotLights[" + iStr + "].diffuse",
                              light->diffuse.x, light->diffuse.y,
                              light->diffuse.z);
            shader->setFloat3("spotLights[" + iStr + "].specular",
                              light->specular.x, light->specular.y,
                              light->specular.z);
            shader->setFloat("spotLights[" + iStr + "].constant",
                             light->constant);
            shader->setFloat("spotLights[" + iStr + "].linear", light->linear);
            shader->setFloat("spotLights[" + iStr + "].quadratic",
                             light->quadratic);
        }
    }
}

} // namespace Engine
