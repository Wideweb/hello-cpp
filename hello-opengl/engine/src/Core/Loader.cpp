#include "Loader.hpp"
#include "AnimationComponent.hpp"
#include "Application.hpp"
#include "CameraComponent.hpp"
#include "CollisionComponent.hpp"
#include "FrameAnimationComponent.hpp"
#include "GroundComponent.hpp"
#include "LocationComponent.hpp"
#include "MaterialComponent.hpp"
#include "Math.hpp"
#include "ObstacleComponent.hpp"
#include "ParalaxScrollingComponent.hpp"
#include "PointLightComponent.hpp"
#include "RenderComponent.hpp"
#include "RigitBodyComponent.hpp"
#include "TextureComponent.hpp"
#include "VelocityComponent.hpp"
#include <fstream>
#include <iostream>
#include <vector>

namespace Engine {

Loader::Loader(std::shared_ptr<EntityManager> entityManager)
    : m_EntityManager(entityManager) {}

Loader::~Loader() {}

void Loader::load(const std::string &path) {
    auto &app = Engine::Application::get();
    auto &textures = app.getTextures();
    auto &shaders = app.getShaders();
    auto &sound = app.getSound();

    std::ifstream in(path, std::ios::in | std::ios::binary);
    std::string attribute;

    std::shared_ptr<Entity> entity;

    while (!in.eof() && in >> attribute) {
        if (attribute == "img") {
            std::string id, src;
            in >> id >> src;
            textures.load(id, src);
        }

        if (attribute == "sound") {
            std::string id, src;
            in >> id >> src;
            sound.add(id, src);
        }

        if (attribute == "shader") {
            std::string id, vertext, fragment;
            in >> id >> vertext >> fragment;
            shaders.load(id, vertext, fragment);
        }

        if (attribute == "entities") {
            std::string path;
            in >> path;
            loadEntities(path);
        }

        in >> std::ws;
    }

    in.close();
}

void Loader::loadEntities(const std::string &path) {
    std::ifstream in(path, std::ios::in | std::ios::binary);
    std::string attribute;

    std::shared_ptr<Entity> entity;

    while (!in.eof() && in >> attribute) {
        if (attribute == "entity") {
            std::string id;
            in >> id;
            entity = m_EntityManager->addEntity(id);
        }

        if (attribute == "location") {
            float x, y;
            in >> x >> y;
            entity->addComponent<LocationComponent>(x, y);
        }

        if (attribute == "velocity") {
            float x, y;
            in >> x >> y;
            entity->addComponent<VelocityComponent>(x, y);
        }

        if (attribute == "collisionRect") {
            float w, h;
            in >> w >> h;
            entity->addComponent<CollisionComponent>(w, h);
        }

        if (attribute == "colliderTriangle") {
            Vec2 v0, v1, v2;
            in >> v0.x >> v0.y;
            in >> v1.x >> v1.y;
            in >> v2.x >> v2.y;

            std::vector<Vec2> vertices = {v0, v1, v2};

            entity->addComponent<CollisionComponent>(vertices);
        }

        if (attribute == "obstacle") {
            entity->addComponent<ObstacleComponent>();
        }

        if (attribute == "ground") {
            entity->addComponent<GroundComponent>();
        }

        if (attribute == "render") {
            int w, h;
            Vec3 color;
            std::string shaderId;

            in >> w >> h;
            in >> color.x >> color.y >> color.z;
            in >> shaderId;

            entity->addComponent<RenderComponent>(w, h, color, shaderId);
        }

        if (attribute == "texture") {
            std::string id;
            Rect source;
            float w, h;
            std::string shaderId;

            in >> id;
            in >> source.x >> source.y >> source.w >> source.h;
            in >> w >> h;
            in >> shaderId;

            entity->addComponent<TextureComponent>(id, source, w, h, shaderId);
            entity->addComponent<MaterialComponent>();
        }

        if (attribute == "material") {
            float r, g, b, shininess;

            in >> r >> g >> b >> shininess;

            auto material = entity->getComponent<MaterialComponent>();
            material->shininess = shininess;
            material->ambient = Vec3(r, g, b);
            material->diffuse = Vec3(r, g, b);
            material->specular = Vec3(r, g, b);
        }

        if (attribute == "pointLight") {
            std::string shaderId;
            in >> shaderId;
            entity->addComponent<PointLightComponent>(shaderId);
        }

        if (attribute == "animation") {
            std::string path;
            in >> path;
            auto scene = loadAnimation(path);

            entity->addComponent<AnimationComponent>(scene);
        }

        if (attribute == "frameAnimation") {
            float y;
            float dx;
            int framesNumber;
            float time;

            in >> y >> dx >> framesNumber >> time;

            auto wait = FrameAnimation(y, dx, framesNumber, time);

            in >> y >> dx >> framesNumber >> time;

            auto move = FrameAnimation(y, dx, framesNumber, time);

            entity->addComponent<FrameAnimationComponent>(wait, move);
        }

        if (attribute == "paralaxScrolling") {
            float scale;
            in >> scale;
            entity->addComponent<ParalaxScrollingComponent>(scale);
        }

        if (attribute == "camera") {
            int leftBound, rightBound, offset;
            in >> leftBound >> rightBound >> offset;
            entity->addComponent<Engine::CameraComponent>(leftBound, rightBound,
                                                          offset);
        }

        if (attribute == "rigitBody") {
            float weight;
            in >> weight;
            entity->addComponent<Engine::RigitBodyComponent>(weight);
        }

        in >> std::ws;
    }

    in.close();
}

AnimationScene Loader::loadAnimation(const std::string &path) {
    std::ifstream in(path, std::ios::in | std::ios::binary);
    std::string attribute;

    std::vector<TimeLine> timeLines;

    while (!in.eof() && in >> attribute) {
        if (attribute == "timeLine") {
            timeLines.emplace_back();
        }

        if (attribute == "animation") {
            std::string propertyName;
            float targetValue, time;

            in >> propertyName >> targetValue >> time;

            AnimationProperty property;
            if (propertyName == "x") {
                property = AnimationProperty::X;
            } else if (propertyName == "y") {
                property = AnimationProperty::Y;
            } else if (propertyName == "scale") {
                property = AnimationProperty::Scale;
            } else if (propertyName == "angle") {
                property = AnimationProperty::Angle;
            }

            timeLines.back().add(Animation(property, targetValue, time));
        }

        if (attribute == "gap") {
            float time;
            in >> time;
            timeLines.back().add(TimeLineGap(time));
        }

        in >> std::ws;
    }

    in.close();

    return AnimationScene(timeLines);
}

} // namespace Engine
