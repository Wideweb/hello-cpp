#include "ImGuiLayer.hpp"
#include "Application.hpp"
#include "EmitterComponent.hpp"
#include "LocationComponent.hpp"
#include "ParalaxScrollingComponent.hpp"
#include "PointLightComponent.hpp"
#include "SpotLightComponent.hpp"
#include "TextureComponent.hpp"

namespace Engine {

const std::string vertexShader =
    R"(
    #version 330 core
    layout(location = 0) in vec2 position;
    layout(location = 1) in vec2 uv;
    layout(location = 2) in vec4 color;

    uniform mat2x3 model;

    out vec2 v_uv;
    out vec4 v_color;

    void main() {
        v_uv = uv;
        v_color = color;

        vec2 pos = vec3(position, 1.0f) * model;
        gl_Position = vec4(pos, 1.0f, 1.0f);
    }
)";

const std::string fragmentShader =
    R"(
    #version 330 core
    in vec2 v_uv;
    in vec4 v_color;

    uniform sampler2D s_texture;

    out vec4 f_color;

    void main() {
        f_color = v_color * texture(s_texture, v_uv);
    }
)";

void ImGuiLayer::onAttach() {
    m_Shader.reset(Shader::create(vertexShader, fragmentShader));

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO &io = ImGui::GetIO();
    io.BackendPlatformName = "custom_micro_engine";
    io.RenderDrawListsFn = nullptr;

    if (io.Fonts->TexID == nullptr) {
        unsigned char *pixels = nullptr;
        int width = 0;
        int height = 0;
        io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
        io.Fonts->TexID = Texture::create(pixels, width, height);
    }

    io.KeyMap[ImGuiKey_Backspace] = ImGuiKey_Backspace;

    io.ClipboardUserData = nullptr;

    entityId = std::string(1024, '\0');
    texture = std::string(1024, '\0');
}

void ImGuiLayer::onUpdate() {}

void ImGuiLayer::onRender() {
    auto &input = Application::get().getInput();
    auto &time = Application::get().getTime();
    auto &window = Application::get().getWindow();
    auto layer = Application::get().getLayers()[0];

    ImGuiIO &io = ImGui::GetIO();

    int dWidth, dHeight;
    window.getDrawableSize(dWidth, dHeight);
    int width = window.getWidth();
    int height = window.getHeight();

    io.DisplaySize = ImVec2(float(width), float(height));
    io.DisplayFramebufferScale =
        ImVec2(width > 0 ? float(dWidth / width) : 0.f,
               height > 0 ? float(dHeight / height) : 0.f);

    io.DeltaTime = time.getDeltaSeconds();
    if (io.DeltaTime <= 0) {
        io.DeltaTime = 0.00001f;
    }

    auto mouse = input.GetMousePosition();
    io.MousePos = ImVec2(mouse.x, height - mouse.y);

    io.MouseDown[0] = input.IsMousePressed(MouseButton::Left);
    io.MouseDown[1] = input.IsMousePressed(MouseButton::Right);
    io.MouseDown[2] = input.IsMousePressed(MouseButton::Middle);

    io.KeysDown[ImGuiKey_Backspace] = input.IsKeyPressed(KeyCode::Backspace);

    io.AddInputCharactersUTF8(input.GetTextInput().data());

    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(200, 0));

    {
        ImGui::Begin("Entity");

        ImGui::Text("Name: ");
        ImGui::SameLine();
        ImGui::InputText("", entityId.data(), entityId.size());

        if (entity != nullptr) {
            auto location = entity->getComponent<LocationComponent>();
            ImGui::Text("Location: ");
            ImGui::InputFloat("x", &location->x, 1.0f, 1.0f, "%.3f");
            ImGui::InputFloat("y", &location->y, 1.0f, 1.0f, "%.3f");
        }

        if (ImGui::Button("Add")) {
            entity = layer->addEntity(entityId);
        }

        if (ImGui::Button("Select")) {
            entity = layer->getEntity(entityId.data());
        }

        ImGui::Text("%.3f ms/frame (%.1f FPS)",
                    1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);

        ImGui::End();

        {
            if (entity != nullptr) {
                if (entity->hasComponent<TextureComponent>()) {
                    auto texture = entity->getComponent<TextureComponent>();

                    ImGui::Begin("Texture");

                    ImGui::InputInt("width", &texture->width, 1.0f, 1.0f);
                    ImGui::InputInt("height", &texture->height, 1.0f, 1.0f);

                    ImGui::Text("Texture source: ");
                    ImGui::InputFloat("left", &texture->source.x, 0.01f, 0.01f,
                                      "%.3f");
                    ImGui::InputFloat("top", &texture->source.y, 0.01f, 0.01f,
                                      "%.3f");
                    ImGui::InputFloat("w", &texture->source.w, 0.01f, 0.01f,
                                      "%.3f");
                    ImGui::InputFloat("h", &texture->source.h, 0.01f, 0.01f,
                                      "%.3f");
                    texture->update();

                    ImGui::End();
                }
            }
        }

        {
            if (entity != nullptr) {
                if (entity->hasComponent<PointLightComponent>()) {
                    auto light = entity->getComponent<PointLightComponent>();

                    ImGui::Begin("Point Light");

                    ImGui::InputFloat("constant", &light->constant, 0.01f, 1.0f,
                                      "%.3f");
                    ImGui::InputFloat("linear", &light->linear, 0.01f, 1.0f,
                                      "%.3f");
                    ImGui::InputFloat("quadratic", &light->quadratic, 0.01f,
                                      1.0f, "%.3f");

                    ImGui::Text("ambient: ");
                    ImGui::InputFloat("ar", &light->ambient.x, 0.01f, 0.01f,
                                      "%.3f");
                    ImGui::InputFloat("ag", &light->ambient.y, 0.01f, 0.01f,
                                      "%.3f");
                    ImGui::InputFloat("ab", &light->ambient.z, 0.01f, 0.01f,
                                      "%.3f");

                    ImGui::Text("diffuse: ");
                    ImGui::InputFloat("dr", &light->diffuse.x, 0.01f, 0.01f,
                                      "%.3f");
                    ImGui::InputFloat("dg", &light->diffuse.y, 0.01f, 0.01f,
                                      "%.3f");
                    ImGui::InputFloat("db", &light->diffuse.z, 0.01f, 0.01f,
                                      "%.3f");

                    ImGui::Text("specular: ");
                    ImGui::InputFloat("sr", &light->specular.x, 0.01f, 0.01f,
                                      "%.3f");
                    ImGui::InputFloat("sg", &light->specular.y, 0.01f, 0.01f,
                                      "%.3f");
                    ImGui::InputFloat("sb", &light->specular.z, 0.01f, 0.01f,
                                      "%.3f");

                    ImGui::End();
                }
            }
        }

        {
            if (entity != nullptr) {
                if (entity->hasComponent<SpotLightComponent>()) {
                    auto light = entity->getComponent<SpotLightComponent>();

                    ImGui::Begin("Spot Light");

                    ImGui::InputFloat("constant", &light->constant, 0.01f, 1.0f,
                                      "%.3f");
                    ImGui::InputFloat("linear", &light->linear, 0.01f, 1.0f,
                                      "%.3f");
                    ImGui::InputFloat("quadratic", &light->quadratic, 0.01f,
                                      1.0f, "%.3f");

                    ImGui::Text("ambient: ");
                    ImGui::InputFloat("ar", &light->ambient.x, 0.01f, 0.01f,
                                      "%.3f");
                    ImGui::InputFloat("ag", &light->ambient.y, 0.01f, 0.01f,
                                      "%.3f");
                    ImGui::InputFloat("ab", &light->ambient.z, 0.01f, 0.01f,
                                      "%.3f");

                    ImGui::Text("diffuse: ");
                    ImGui::InputFloat("dr", &light->diffuse.x, 0.01f, 0.01f,
                                      "%.3f");
                    ImGui::InputFloat("dg", &light->diffuse.y, 0.01f, 0.01f,
                                      "%.3f");
                    ImGui::InputFloat("db", &light->diffuse.z, 0.01f, 0.01f,
                                      "%.3f");

                    ImGui::Text("specular: ");
                    ImGui::InputFloat("sr", &light->specular.x, 0.01f, 0.01f,
                                      "%.3f");
                    ImGui::InputFloat("sg", &light->specular.y, 0.01f, 0.01f,
                                      "%.3f");
                    ImGui::InputFloat("sb", &light->specular.z, 0.01f, 0.01f,
                                      "%.3f");

                    ImGui::Text("direction: ");
                    ImGui::InputFloat("dx", &light->direction.x, 0.01f, 0.01f,
                                      "%.3f");
                    ImGui::InputFloat("dy", &light->direction.y, 0.01f, 0.01f,
                                      "%.3f");

                    ImGui::Text("cut off: ");
                    ImGui::InputFloat("in", &light->cutOff, 0.01f, 0.01f,
                                      "%.3f");
                    ImGui::Text("outer cut off: ");
                    ImGui::InputFloat("out", &light->outerCutOff, 0.01f, 0.01f,
                                      "%.3f");

                    ImGui::End();
                }
            }
        }

        {
            if (entity != nullptr) {
                if (entity->hasComponent<EmitterComponent>()) {
                    auto emmiter = entity->getComponent<EmitterComponent>();

                    ImGui::Begin("Emmiter");

                    ImGui::InputInt("buffer", &emmiter->bufferSize, 1.0f, 1.0f);
                    ImGui::InputInt("width", &emmiter->width, 1.0f, 1.0f);
                    ImGui::InputFloat("interval", &emmiter->interval, 0.01f,
                                      1.0f, "%.3f");

                    ImGui::End();
                }
            }
        }
    }

    ImGui::Render();

    draw(ImGui::GetDrawData());
}

void ImGuiLayer::onWindowEvent(WindowEvent &e) {}

void ImGuiLayer::onDetach() {
    void *ptr = ImGui::GetIO().Fonts->TexID;
    ImGui::DestroyContext();
}

void ImGuiLayer::draw(ImDrawData *drawData) {
    auto &render = Application::get().getRender();

    // Avoid rendering when minimized, scale coordinates for retina displays
    // (screen coordinates != framebuffer coordinates)
    ImGuiIO &io = ImGui::GetIO();
    int fbWidth = int(io.DisplaySize.x * io.DisplayFramebufferScale.x);
    int fbHeight = int(io.DisplaySize.y * io.DisplayFramebufferScale.y);
    if (fbWidth == 0 || fbHeight == 0) {
        return;
    }
    drawData->ScaleClipRects(io.DisplayFramebufferScale);

    Mat2x3 model =
        Mat2x3::move(Vec2(-1.0f, 1.0f)) *
        Mat2x3::scale(2.0f / io.DisplaySize.x, -2.0f / io.DisplaySize.y);

    m_Shader->setMatrix2x3("model", model.data());

    for (int n = 0; n < drawData->CmdListsCount; n++) {
        const ImDrawList *cmdList = drawData->CmdLists[n];
        const ImDrawIdx *idx_buffer_offset = nullptr;

        std::shared_ptr<VertexArray> vertexArray(VertexArray::create());
        vertexArray->bind();

        BufferLayout layout = {
            {ShaderDataType::Float2, "position"},
            {ShaderDataType::Float2, "uv"},
            {ShaderDataType::Float4, "color"},
        };

        std::vector<float> vertices;
        for (const ImDrawVert &vertex : cmdList->VtxBuffer) {
            vertices.push_back(vertex.pos.x);
            vertices.push_back(vertex.pos.y);
            vertices.push_back(vertex.uv.x);
            vertices.push_back(vertex.uv.y);

            float r = float(vertex.col & 255) / 255.0f;
            float g = float((vertex.col >> 8) & 255) / 255.0f;
            float b = float((vertex.col >> 16) & 255) / 255.0f;
            float a = float((vertex.col >> 24) & 255) / 255.0f;

            vertices.push_back(r);
            vertices.push_back(g);
            vertices.push_back(b);
            vertices.push_back(a);
        }
        std::shared_ptr<VertexBuffer> vertexBuffer(
            VertexBuffer::create(vertices));

        std::vector<uint32_t> indexes(cmdList->IdxBuffer.begin(),
                                      cmdList->IdxBuffer.end());
        std::shared_ptr<IndexBuffer> indexBuffer(IndexBuffer::create(indexes));

        vertexBuffer->setLayout(layout);
        vertexArray->addVertexBuffer(vertexBuffer);
        vertexArray->setIndexBuffer(indexBuffer);

        for (size_t i = 0; i < cmdList->CmdBuffer.Size; i++) {
            const ImDrawCmd *pcmd = &cmdList->CmdBuffer[i];
            assert(pcmd->UserCallback == nullptr); // we not use it

            auto texture(reinterpret_cast<Texture *>(pcmd->TextureId));

            render.drawTexture(m_Shader, vertexArray, texture);
        }
    }
}

void ImGuiLayer::onMouseEvent(Engine::MouseEvent &e) {
    ImGuiIO &io = ImGui::GetIO();
    if (io.WantCaptureMouse) {
        return;
    }

    e.handled = true;

    auto &camera = Application::get().getCamera();
    auto &input = Application::get().getInput();

    if (e.type == Engine::EventType::MouseDown) {
        bool found = false;
        auto layer = Application::get().getLayers()[0];
        auto entities = layer->getEntities().getAll();
        for (size_t i = entities.size() - 1; i > 0; i--) {
            auto entity_ = entities[i];
            auto location = entity_->getComponent<LocationComponent>();

            float paralaxScale = 1.0f;

            if (entity_->hasComponent<ParalaxScrollingComponent>()) {
                auto pralax =
                    entity_->getComponent<ParalaxScrollingComponent>();
                paralaxScale = pralax->scale;
            }

            if (entity_->hasComponent<TextureComponent>()) {
                auto texture = entity_->getComponent<TextureComponent>();
                float left = location->x - texture->width / 2;
                float right = location->x + texture->width / 2;
                float top = location->y + texture->height / 2;
                float bottom = location->y - texture->height / 2;

                int mY = e.y + camera.y * paralaxScale;
                int mX = e.x + camera.x * paralaxScale;

                if (mX > left && mX < right && mY > bottom && mY < top) {
                    entity = entity_;
                    std::string name = entity->getName();
                    name.copy(entityId.data(), name.size());
                    entityId[name.size()] = '\0';

                    mouseOffsetX = location->x - mX;
                    mouseOffsetY = location->y - mY;

                    found = true;

                    break;
                }
            }
        }

        if (!found) {
            entity = nullptr;
            entityId[0] = '\0';
        }
    }

    if (entity != nullptr && e.type == Engine::EventType::MouseMoved) {
        if (input.IsMousePressed(MouseButton::Left)) {
            float paralaxScale = 1.0f;

            if (entity->hasComponent<ParalaxScrollingComponent>()) {
                auto pralax = entity->getComponent<ParalaxScrollingComponent>();
                paralaxScale = pralax->scale;
            }

            auto location = entity->getComponent<LocationComponent>();
            location->x = e.x + camera.x * paralaxScale + mouseOffsetX;
            location->y = e.y + camera.y * paralaxScale + mouseOffsetY;
        }
    }
}

} // namespace Engine
