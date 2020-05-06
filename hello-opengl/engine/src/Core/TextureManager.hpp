#pragma once

#include "Texture.hpp"
#include <map>
#include <memory>
#include <string>

namespace Engine {

class TextureManager {
  private:
    std::map<std::string, std::shared_ptr<Texture>> m_Map;

  public:
    void load(const std::string &name, const std::string &path);
    std::shared_ptr<Texture> get(const std::string &name);
};

} // namespace Engine
