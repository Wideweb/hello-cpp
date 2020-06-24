#include "SystemStack.hpp"
#include "AISystem.hpp"
#include "AnimationSystem.hpp"
#include "AttackSystem.hpp"
#include "CameraSystem.hpp"
#include "CollisionSystem.hpp"
#include "EmitterSystem.hpp"
#include "EntityManager.hpp"
#include "GroundCollisionSystem.hpp"
#include "LightSystem.hpp"
#include "MorphingSystem.hpp"
#include "MoveSystem.hpp"
#include "PhysicsSystem.hpp"
#include "RenderSystem.hpp"
#include "SpotLightSystem.hpp"
#include "SteeringSystem.hpp"
#include "TextureSystem.hpp"

#include <vector>

namespace Engine {

SystemStack::SystemStack() {
    m_Systems.push_back(new AISystem());
    m_Systems.push_back(new PhysicsSystem());
    m_Systems.push_back(new SteeringSystem());
    m_Systems.push_back(new AttackSystem());
    m_Systems.push_back(new CollisionSystem());
    m_Systems.push_back(new GroundCollisionSystem());
    m_Systems.push_back(new MoveSystem());
    m_Systems.push_back(new CameraSystem());
    m_Systems.push_back(new RenderSystem());
    m_Systems.push_back(new MorphingSystem());
    m_Systems.push_back(new AnimationSystem());
    m_Systems.push_back(new LightSystem());
    m_Systems.push_back(new SpotLightSystem());
    m_Systems.push_back(new TextureSystem());
    m_Systems.push_back(new EmitterSystem());
}

void SystemStack::exec(EntityManager &entities) {
    for (auto system : m_Systems) {
        system->exec(entities);
    }
}

} // namespace Engine
