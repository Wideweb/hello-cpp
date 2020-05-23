#include "ImGuiLayer.hpp"
#include "Application.hpp"
#include "LocationComponent.hpp"

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
    io.MousePos = ImVec2(mouse.x, mouse.y);

    io.MouseDown[0] = input.IsMousePressed(MouseButton::Left);
    io.MouseDown[1] = input.IsMousePressed(MouseButton::Right);
    io.MouseDown[2] = input.IsMousePressed(MouseButton::Middle);

    io.KeysDown[ImGuiKey_Backspace] = input.IsKeyPressed(KeyCode::Backspace);

    io.AddInputCharactersUTF8(input.GetTextInput().data());

    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(200, 0));

    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Entity");

        ImGui::Text("Name: ");
        ImGui::SameLine();
        ImGui::InputText("id", entityId.data(), entityId.size());

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
    }

    ImGui::Render();

    draw(ImGui::GetDrawData());
}

void ImGuiLayer::onMouseEvent(MouseEvent &e) {}

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

} // namespace Engine
