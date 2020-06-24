#include "EntitySerializer.hpp"
#include "AnimationLoader.hpp"

namespace Engine {

Entity *EntitySerializer::from(std::istringstream &in) {
    std::string attribute;
    Entity *entity;

    while (!in.eof() && in >> attribute) {
        if (attribute == "entity") {
            std::string id;
            in >> id;
            entity = new Entity(id);
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

        if (attribute == "groundCollision") {
            float w, h;
            in >> w >> h;
            entity->addComponent<GroundCollisionComponent>(w, h);
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

            in >> w >> h;
            in >> color.x >> color.y >> color.z;

            entity->addComponent<RenderComponent>(w, h, color);
            entity->addComponent<MaterialComponent>();
        }

        if (attribute == "texture") {
            std::string id;
            Rect source;
            float w, h;
            float alpha;

            in >> id;
            in >> source.x >> source.y >> source.w >> source.h;
            in >> w >> h;
            in >> alpha;

            entity->addComponent<TextureComponent>(id, source, w, h, alpha);
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
            Vec3 ambient;
            Vec3 diffuse;
            Vec3 specular;
            float constant;
            float linear;
            float quadratic;

            in >> ambient.x >> ambient.y >> ambient.z;
            in >> diffuse.x >> diffuse.y >> diffuse.z;
            in >> specular.x >> specular.y >> specular.z;
            in >> constant >> linear >> quadratic;

            entity->addComponent<PointLightComponent>(
                ambient, diffuse, specular, constant, linear, quadratic);
        }

        if (attribute == "spotLight") {
            Vec3 ambient;
            Vec3 diffuse;
            Vec3 specular;
            float constant;
            float linear;
            float quadratic;
            Vec2 direction;
            float cutOff;
            float outerCutOff;

            in >> ambient.x >> ambient.y >> ambient.z;
            in >> diffuse.x >> diffuse.y >> diffuse.z;
            in >> specular.x >> specular.y >> specular.z;
            in >> constant >> linear >> quadratic;
            in >> direction.x >> direction.y;
            in >> cutOff >> outerCutOff;

            entity->addComponent<SpotLightComponent>(
                ambient, diffuse, specular, constant, linear, quadratic,
                direction, cutOff, outerCutOff);
        }

        if (attribute == "ignoreLight") {
            entity->addComponent<IgnoreLightComponent>();
        }

        if (attribute == "animation") {
            std::string path;
            bool isActive;

            in >> path;
            in >> isActive;

            auto scene = AnimationLoader::load(path);

            entity->addComponent<AnimationComponent>(scene)->isActive =
                isActive;
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

        if (attribute == "frame") {
            int framesNumber;
            entity->addComponent<FrameComponent>(framesNumber);
        }

        if (attribute == "paralaxScrolling") {
            float scale;
            in >> scale;
            entity->addComponent<ParalaxScrollingComponent>(scale);
        }

        if (attribute == "camera") {
            int leftBound, rightBound, offset;
            in >> leftBound >> rightBound >> offset;
            entity->addComponent<CameraComponent>(leftBound, rightBound,
                                                  offset);
        }

        if (attribute == "rigitBody") {
            float weight;
            in >> weight;
            entity->addComponent<RigitBodyComponent>(weight);
        }

        if (attribute == "parent") {
            std::string parent;
            in >> parent;
            entity->addComponent<ParentComponent>(parent);
        }

        if (attribute == "steering") {
            std::string target;
            in >> target;
            entity->addComponent<SteeringComponent>(target);
        }

        if (attribute == "enemy") {
            entity->addComponent<EnemyComponent>();
        }

        if (attribute == "attack") {
            Rect r;
            in >> r.x >> r.y >> r.w >> r.h;
            entity->addComponent<AttackComponent>(r);
        }

        if (attribute == "direction") {
            int x, y;
            in >> x >> y;
            entity->addComponent<DirectionComponent>(x, y);
        }

        if (attribute == "emitter") {
            std::string prefab;
            int buffer, width;
            float interval;

            in >> prefab;
            in >> buffer >> width;
            in >> interval;

            entity->addComponent<EmitterComponent>(prefab, buffer, width,
                                                   interval);
        }

        if (attribute == "inactive") {
            entity->isActive = false;
        }

        if (attribute == "group") {
            std::string group;
            in >> group;
            entity->addComponent<GroupComponent>(group);
        }

        in >> std::ws;
    }

    return entity;
}

} // namespace Engine
