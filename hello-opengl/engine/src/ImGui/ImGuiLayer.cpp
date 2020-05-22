#include "ImGuiLayer.hpp"
#include "Application.hpp"

namespace Engine {

const std::string vertexShader =
    R"(
    #version 330 core
    layout(location = 0) in vec2 position;
    layout(location = 1) in vec2 uv;
    layout(location = 2) in vec4 color;

    uniform mat3 model

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

    void main() {
        gl_FragColor = v_color * texture2D(s_texture, v_uv);
    }
)";

void ImGuiLayer::onAttach() {
    m_Shader.reset(Shader::create(vertexShader, fragmentShader));

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO &io = ImGui::GetIO();
    io.BackendPlatformName = "custom_micro_engine";
    io.RenderDrawListsFn = nullptr; // call ImGui::GetDrawData()
                                    // after ImGui::Render() to get the
                                    // same ImDrawData pointer.
}

void ImGuiLayer::onRender() {
    auto &input = Application::get().getInput();
    auto &time = Application::get().getTime();
    auto &window = Application::get().getWindow();

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

    // Start the frame. This call will update the io.WantCaptureMouse,
    // io.WantCaptureKeyboard flag that you can use to dispatch inputs (or not)
    // to your application.
    ImGui::NewFrame();

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
        Mat2x3::scale(2.0f / io.DisplaySize.x, -2.0f / io.DisplaySize.y) *
        Mat2x3::move(Vec2(-1.0f, 1.0f));

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

            float r = float(vertex.col & 8);
            float g = float((vertex.col << 8) & 8);
            float b = float((vertex.col << 16) & 8);
            float a = float((vertex.col << 24) & 8);

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

            std::shared_ptr<Texture> texture(Texture::create(indexes));
            om::texture *tex = reinterpret_cast<om::texture *>(pcmd->TextureId);

            render.drawTexture(m_Shader, vertexArray, texture);
        }
    }
}

} // namespace Engine
