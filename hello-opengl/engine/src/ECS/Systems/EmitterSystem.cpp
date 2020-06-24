#include "EmitterSystem.hpp"
#include "AIComponent.hpp"
#include "Application.hpp"
#include "BehaviourTree.hpp"
#include "EmitterComponent.hpp"
#include "EntitySerializer.hpp"
#include "LocationComponent.hpp"
#include "VelocityComponent.hpp"

#include <cmath>
#include <sstream>

namespace Engine {

void EmitterSystem::exec(EntityManager &entities) {
    auto &app = Application::get();
    auto &time = app.getTime();

    for (auto entity : entities.getAll()) {
        if (entity->hasComponent<EmitterComponent>()) {
            auto emitter = entity->getComponent<EmitterComponent>();
            auto location = entity->getComponent<LocationComponent>();

            emitter->elapsedTime += time.getDeltaSeconds();
            if (emitter->elapsedTime < emitter->interval) {
                continue;
            }
            emitter->elapsedTime = 0;

            Entity *projectile;

            if (emitter->counter < emitter->bufferSize) {
                std::ostringstream oss;
                auto prefab = entities.get(emitter->entity);
                prefab->serialize(oss);
                std::istringstream iss(oss.str());
                projectile = EntitySerializer::from(iss);

                std::ostringstream name;
                name << emitter->entity;
                name << emitter->counter;
                projectile->setName(name.str());
                emitter->counter++;

                auto blackboard = std::make_shared<Blackboard>();
                blackboard->setPtr("entity", projectile);
                blackboard->setFloat("wait", 0.1);

                // clang-format off
                auto state = new BlackboardManager(
                    blackboard,
                    new SelectorTask({
                        new Inverter(new ActiveTask()),
                        new SequenceTask({
                            new OnGroundTask(),
                            new WaitTask(),
                            new FreeTask(),
                        }),
                        new MoveTask(),
                    })
                );
                // clang-format on
                projectile->addComponent<AIComponent>(state);

                entities.addEntity(projectile);
            } else {
                std::ostringstream name;
                name << emitter->entity;

                if (emitter->index == emitter->bufferSize) {
                    emitter->index = 0;
                }

                name << emitter->index;
                emitter->index++;

                projectile = entities.get(name.str()).get();

                if (!projectile || projectile->isActive) {
                    continue;
                }
            }

            float dx = -(emitter->width / 2) +
                       (rand() % static_cast<int>(emitter->width));
            float dy = 500 + (rand() % static_cast<int>(100));

            auto projectileLocation =
                projectile->getComponent<LocationComponent>();

            projectileLocation->x = location->x + dx;
            projectileLocation->y = location->y + dy;

            auto projectileVelocity =
                projectile->getComponent<VelocityComponent>();

            projectileVelocity->x = -0.3;
            projectileVelocity->y = -1 * (5 + (rand() % static_cast<int>(2)));

            projectile->isActive = true;
        }
    }
}

} // namespace Engine
