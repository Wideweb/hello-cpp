#pragma once

#include "Entity.hpp"
#include "Math.hpp"

namespace Engine {

class AttackComponent : public Component {
  public:
    std::vector<Vec2> vertices;

    AttackComponent(const Rect &range) {
        vertices.push_back(Vec2(range.x, range.y));
        vertices.push_back(Vec2(range.x, range.y + range.h));
        vertices.push_back(Vec2(range.x + range.w, range.y + range.h));
        vertices.push_back(Vec2(range.x + range.w, range.y));
    }

    virtual void serialize(std::ostringstream &out) override {
        Rect r;
        r.x = vertices[0].x;
        r.y = vertices[0].y;
        r.w = vertices[2].x - vertices[0].x;
        r.h = vertices[2].y - vertices[0].y;

        out << "attack ";
        out << r;
        out << std::endl;
    }
};

} // namespace Engine