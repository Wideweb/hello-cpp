#include "Layer.hpp"
#include "Loader.hpp"

namespace Engine {

Layer::Layer() { m_EntityManager.reset(new EntityManager()); }

std::shared_ptr<Entity> Layer::addEntity(const std::string &name) {
    return m_EntityManager->addEntity(name);
}

std::shared_ptr<Entity> Layer::getEntity(const std::string &name) {
    return m_EntityManager->get(name);
}

EntityManager &Layer::getEntities() { return *m_EntityManager; }

void Layer::clear() { m_EntityManager->clear(); }

void Layer::load(const std::string &configPath) {
    Loader loader(m_EntityManager);
    loader.load(configPath);
}

} // namespace Engine