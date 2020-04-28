#include "System.hpp"
#include <vector>

namespace Engine {

class SystemStack {
  private:
    std::vector<System *> m_Systems;

  public:
    SystemStack();
    void exec(std::vector<std::shared_ptr<Entity>> &entities);
};

} // namespace Engine
