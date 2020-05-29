#include "InteractionSystem.hpp"
#include "Application.hpp"
#include "InteractionComponent.hpp"
#include "LocationComponent.hpp"
#include <cmath>

namespace Engine {

void InteractionSystem::exec(EntityManager &entities) {
    auto &app = Application::get();
    auto &eventHandler = app.getEventHandler();

    for (auto entity : entities.getAll()) {
        if (!entity->hasComponent<InteractionComponent>()) {
            continue;
        }

        auto location = entity->getComponent<LocationComponent>();
        auto interaction = entity->getComponent<InteractionComponent>();

        auto subject = entities.get(interaction->subject);
        auto subjectLocation = subject->getComponent<LocationComponent>();

        BeginInteractionEvent event;
        event.subject = subject->getName();
        event.object = entity->getName();
        eventHandler.send<BeginInteractionEvent>(event);
    }
}

} // namespace Engine
