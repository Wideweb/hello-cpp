#include "Layer.hpp"

namespace Engine {

std::shared_ptr<Entity> Layer::addEntity(std::string name) {
    return m_EntityManager.addEntity(name);
}

EntityManager &Layer::getEntities() { return m_EntityManager; }

} // namespace Engine