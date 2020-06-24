#include "Loader.hpp"
#include "Application.hpp"
#include "ECS.hpp"
#include "EntitySerializer.hpp"
#include "Math.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace Engine {

Loader::Loader(std::shared_ptr<EntityManager> entityManager)
    : m_EntityManager(entityManager) {}

Loader::~Loader() {}

void Loader::load(const std::string &path) {
    auto &app = Application::get();
    auto &textures = app.getTextures();
    auto &shaders = app.getShaders();
    auto &sound = app.getSound();

    std::ifstream in(path, std::ios::in | std::ios::binary);
    std::string attribute;

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
    std::ostringstream dto;
    std::string line;

    while (std::getline(in, line)) {
        if (line.empty()) {
            std::istringstream in(dto.str());
            auto entity = EntitySerializer::from(in);
            m_EntityManager->addEntity(entity);
            dto.str(std::string());
        } else {
            dto << std::endl << line;
        }
    }

    if (!dto.eof()) {
        std::istringstream in(dto.str());
        auto entity = EntitySerializer::from(in);
        m_EntityManager->addEntity(entity);
    }

    in.close();
}

} // namespace Engine
