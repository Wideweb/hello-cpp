#include <map>
#include <memory>
#include <string>

class Level {
  public:
    virtual void load() = 0;
    virtual void unload() = 0;
};

class LevelManager {
  private:
    std::map<std::string, std::shared_ptr<Level>> m_Map;

  public:
    void add(const std::string &name, const Level *level);
    void load(const std::string &name);
    void unload(const std::string &name);
};
