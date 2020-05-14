#pragma once

#include "Task.hpp"
#include <vector>

namespace Engine {

class ParallelTask : public Task {
  private:
    std::vector<Task *> m_Tasks;

  public:
    ParallelTask(const std::vector<Task *> tasks) : m_Tasks(tasks) {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        TaskStatus result = TaskStatus::Fail;

        for (auto task : m_Tasks) {

            TaskStatus taskStatus = TaskStatus::Running;
            do {
                taskStatus = task->update(blackboard);
            } while (taskStatus == TaskStatus::Running);

            if (taskStatus == TaskStatus::Success) {
                result = TaskStatus::Success;
            }
        }

        return result;
    }
};

} // namespace Engine
