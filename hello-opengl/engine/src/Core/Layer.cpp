#include "Layer.hpp"

namespace Engine {

std::shared_ptr<Entity> Layer::addEntity(std::string name) {
    return m_EntityManager.addEntity(name);
}

std::vector<std::shared_ptr<Entity>> &Layer::getEntities() {
    return m_EntityManager.getAll();
}

} // namespace Engine