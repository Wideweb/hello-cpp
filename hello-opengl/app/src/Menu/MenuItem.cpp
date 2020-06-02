#include "MenuItem.hpp"

MenuItem::MenuItem(const std::string &enityId, MenuItemLinkType type,
                   std::string link)
    : type(type), link(link) {
    m_EnityId = enityId;
}

void MenuItem::load(Context *context) {
    m_Entity = context->getEntity(m_EnityId);
}

void MenuItem::setOnSelectEvent(
    std::function<void(const MenuItem &)> callback) {
    m_onSelect = callback;
}

void MenuItem::update() {
    auto &input = Engine::Application::get().getInput();

    Engine::Vec2 pos = input.GetMousePosition();

    auto location = m_Entity->getComponent<Engine::LocationComponent>();
    auto texture = m_Entity->getComponent<Engine::TextureComponent>();

    int left = location->x - texture->width / 2;
    int right = location->x + texture->width / 2;
    int top = location->y + texture->height / 2;
    int bottom = location->y - texture->height / 2;

    if (left < pos.x && right > pos.x && top > pos.y && bottom < pos.y) {
        onMouseIn();

        if (input.IsMousePressed(Engine::MouseButton::Left)) {
            m_onSelect(*this);
        }
    } else {
        onMouseOut();
    }
}

void MenuItem::onMouseIn() {
    auto material = m_Entity->getComponent<Engine::MaterialComponent>();
    float v = 1;

    material->ambient.x = v;
    material->ambient.y = v;
    material->ambient.z = v;
    material->diffuse.x = v;
    material->diffuse.y = v;
    material->diffuse.z = v;
    material->specular.x = v;
    material->specular.y = v;
    material->specular.z = v;
    material->shininess = 0;
}

void MenuItem::onMouseOut() {
    auto material = m_Entity->getComponent<Engine::MaterialComponent>();
    float v = 0.5;

    material->ambient.x = v;
    material->ambient.y = v;
    material->ambient.z = v;
    material->diffuse.x = v;
    material->diffuse.y = v;
    material->diffuse.z = v;
    material->specular.x = v;
    material->specular.y = v;
    material->specular.z = v;
    material->shininess = 0;
}

void MenuItem::unload(Context *) {}