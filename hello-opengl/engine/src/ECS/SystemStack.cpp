#include "SystemStack.hpp"
#include "AISystem.hpp"
#include "CameraSystem.hpp"
#include "CollisionSystem.hpp"
#include "ControlSystem.hpp"
#include "EntityManager.hpp"
#include "MorphingSystem.hpp"
#include "MoveSystem.hpp"
#include "PhysicsSystem.hpp"
#include "RenderSystem.hpp"
#include <vector>

namespace Engine {

SystemStack::SystemStack() {
    m_Systems.push_back(new AISystem());
    m_Systems.push_back(new ControlSystem());
    m_Systems.push_back(new PhysicsSystem());
    m_Systems.push_back(new CollisionSystem());
    m_Systems.push_back(new MoveSystem());
    m_Systems.push_back(new CameraSystem());
    m_Systems.push_back(new RenderSystem());
    m_Systems.push_back(new MorphingSystem());
}

void SystemStack::exec(std::vector<std::shared_ptr<Entity>> &entities) {
    for (auto system : m_Systems) {
        system->exec(entities);
    }
}

} // namespace Engine