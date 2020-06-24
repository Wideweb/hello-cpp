#pragma once

#include "Entity.hpp"
#include <map>
#include <memory>
#include <string>

namespace Engine {

template <typename T> using BlackboardData = std::map<std::string, T>;

class Blackboard {
  private:
    std::shared_ptr<Blackboard> m_Parent;
    BlackboardData<float> m_floatData;
    BlackboardData<int> m_intData;
    BlackboardData<void *> m_ptrData;

  public:
    Blackboard() {}

    virtual ~Blackboard() = default;

    void setParent(const std::shared_ptr<Blackboard> parent) {
        m_Parent = parent;
    }

    void setFloat(const std::string key, float value) {
        m_floatData[key] = value;
    }

    float getFloat(const std::string key) {
        auto it = m_floatData.find(key);

        if (it != m_floatData.end()) {
            return it->second;
        }

        if (m_Parent != nullptr) {
            return m_Parent->getFloat(key);
        }

        return 0.0f;
    }

    void setInt(const std::string key, float value) { m_intData[key] = value; }

    int getInt(const std::string key) {
        auto it = m_intData.find(key);

        if (it != m_intData.end()) {
            return it->second;
        }

        if (m_Parent != nullptr) {
            return m_Parent->getFloat(key);
        }

        return 0.0f;
    }

    template <typename T> T *getPtr(const std::string key) {
        auto it = m_ptrData.find(key);

        if (it != m_ptrData.end()) {
            return static_cast<T *>(it->second);
        }

        if (m_Parent != nullptr) {
            return m_Parent->getPtr<T>(key);
        }

        return nullptr;
    }

    template <typename T> void setPtr(const std::string key, T *value) {
        m_ptrData[key] = static_cast<void *>(value);
    }
};

} // namespace Engine
