#pragma once

#include "Task.hpp"

namespace Engine {

class TaskDecorator : public Task {
  protected:
    Task *m_Task;

  public:
    TaskDecorator(Task *task) : m_Task(task) {}
};

} // namespace Engine
