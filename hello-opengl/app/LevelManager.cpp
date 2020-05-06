#include "LevelManager.hpp"

void LevelManager::add(const std::string &name, const Level *level) {
    m_Map[name].reset(level);
}

void LevelManager::load(const std::string &name) { m_Map[name]->load(); }

void LevelManager::unload(const std::string &name) { m_Map[name]->unload(); }
