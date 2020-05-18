#include "ImGuiLayer.hpp"
#include "Application.hpp"
#include "imgui.h"

void ImGuiLayer::onAttach() {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO &io = ImGui::GetIO();
    io.BackendPlatformName = "custom_micro_engine";

    // clang-format off
    io.KeyMap[ImGuiKey_Tab]        = SDL_SCANCODE_TAB;
    io.KeyMap[ImGuiKey_LeftArrow]  = SDL_SCANCODE_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow]    = SDL_SCANCODE_UP;
    io.KeyMap[ImGuiKey_DownArrow]  = SDL_SCANCODE_DOWN;
    io.KeyMap[ImGuiKey_PageUp]     = SDL_SCANCODE_PAGEUP;
    io.KeyMap[ImGuiKey_PageDown]   = SDL_SCANCODE_PAGEDOWN;
    io.KeyMap[ImGuiKey_Home]       = SDL_SCANCODE_HOME;
    io.KeyMap[ImGuiKey_End]        = SDL_SCANCODE_END;
    io.KeyMap[ImGuiKey_Insert]     = SDL_SCANCODE_INSERT;
    io.KeyMap[ImGuiKey_Delete]     = SDL_SCANCODE_DELETE;
    io.KeyMap[ImGuiKey_Backspace]  = SDL_SCANCODE_BACKSPACE;
    io.KeyMap[ImGuiKey_Space]      = SDL_SCANCODE_SPACE;
    io.KeyMap[ImGuiKey_Enter]      = SDL_SCANCODE_RETURN;
    io.KeyMap[ImGuiKey_Escape]     = SDL_SCANCODE_ESCAPE;
    io.KeyMap[ImGuiKey_A]          = SDL_SCANCODE_A;
    io.KeyMap[ImGuiKey_C]          = SDL_SCANCODE_C;
    io.KeyMap[ImGuiKey_V]          = SDL_SCANCODE_V;
    io.KeyMap[ImGuiKey_X]          = SDL_SCANCODE_X;
    io.KeyMap[ImGuiKey_Y]          = SDL_SCANCODE_Y;
    io.KeyMap[ImGuiKey_Z]          = SDL_SCANCODE_Z;
    // clang-format on

    io.RenderDrawListsFn =
        imgui_to_engine_render; // Alternatively you can set this to
                                // NULL and call ImGui::GetDrawData()
                                // after ImGui::Render() to get the
                                // same ImDrawData pointer.
    io.SetClipboardTextFn = ImGui_ImplSdlGL3_SetClipboardText;
    io.GetClipboardTextFn = ImGui_ImplSdlGL3_GetClipboardText;
    io.ClipboardUserData = nullptr;

    io.SetClipboardTextFn = ImGui_ImplSdlGL3_SetClipboardText;
    io.GetClipboardTextFn = ImGui_ImplSdlGL3_GetClipboardText;
    io.ClipboardUserData = nullptr;
}

void ImGuiLayer::onDetach() {
    ImGui_ImplSdlGL3_InvalidateDeviceObjects();
    ImGui::DestroyContext();
}

void ImGuiLayer::onUpdate() {}

void ImGuiLayer::onRender() {
    

    ImGuiIO &io = ImGui::GetIO();

    if (io.Fonts->TexID == nullptr) {
        ImGui_ImplSdlGL3_CreateDeviceObjects();
    }

    // Setup display size (every frame to accommodate for window resizing)
    int w, h;
    int display_w, display_h;
    SDL_GetWindowSize(window, &w, &h);
    SDL_GL_GetDrawableSize(window, &display_w, &display_h);
    io.DisplaySize = ImVec2(float(w), float(h));
    io.DisplayFramebufferScale = ImVec2(w > 0 ? float(display_w / w) : 0.f,
                                        h > 0 ? float(display_h / h) : 0.f);

    io.DeltaTime = Application::getTime()->getDeltaSeconds();
    if (io.DeltaTime <= 0) {
        io.DeltaTime = 0.00001f;
    }

    // Setup inputs
    // (we already got mouse wheel, keyboard keys & characters from
    // SDL_PollEvent())
    int mx, my;
    Uint32 mouseMask = SDL_GetMouseState(&mx, &my);
    if (SDL_GetWindowFlags(window) & SDL_WINDOW_MOUSE_FOCUS)
        io.MousePos = ImVec2(float(mx), float(my));
    else
        io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);

    io.MouseDown[0] =
        g_MousePressed[0] || (mouseMask & SDL_BUTTON(SDL_BUTTON_LEFT)) !=
                                 0; // If a mouse press event came, always pass
                                    // it as "mouse held this frame", so we
                                    // don't miss click-release events that are
                                    // shorter than 1 frame.
    io.MouseDown[1] =
        g_MousePressed[1] || (mouseMask & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0;
    io.MouseDown[2] =
        g_MousePressed[2] || (mouseMask & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0;
    g_MousePressed[0] = g_MousePressed[1] = g_MousePressed[2] = false;

    io.MouseWheel = g_MouseWheel;
    g_MouseWheel = 0.0f;

    // Hide OS mouse cursor if ImGui is drawing it
    SDL_ShowCursor(io.MouseDrawCursor ? 0 : 1);

    // Start the frame. This call will update the io.WantCaptureMouse,
    // io.WantCaptureKeyboard flag that you can use to dispatch inputs (or not)
    // to your application.
    ImGui::NewFrame();
}

void ImGuiLayer::onMouseEvent(MouseEvent &e) {}

void ImGuiLayer::onWindowEvent(WindowEvent &e) {}

bool ImGui_ImplSdlGL3_CreateDeviceObjects() {
    const GLchar *vertex_shader =
        //"#version 150\n"
        "#if defined(GL_ES)\n"
        "precision highp float;\n"
        "#endif //GL_ES\n"
        "uniform mat3 ProjMtx;\n"
        "attribute vec2 Position;\n"
        "attribute vec2 UV;\n"
        "attribute vec4 Color;\n"
        "varying vec2 Frag_UV;\n"
        "varying vec4 Frag_Color;\n"
        "void main()\n"
        "{\n"
        "	Frag_UV = UV;\n"
        "	Frag_Color = Color;\n"
        "	gl_Position = vec4(ProjMtx * vec3(Position.xy,1), 1);\n"
        "}\n";

    const GLchar *fragment_shader =
        //"#version 150\n"
        "#if defined(GL_ES)\n"
        "precision highp float;\n"
        "#endif //GL_ES\n"
        "uniform sampler2D Texture;\n"
        "varying vec2 Frag_UV;\n"
        "varying vec4 Frag_Color;\n"
        //"out vec4 Out_Color;\n"
        "void main()\n"
        "{\n"
        "	gl_FragColor = Frag_Color * texture2D( Texture, Frag_UV);\n"
        "}\n";

    g_im_gui_shader =
        new om::shader_gl_es20(vertex_shader, fragment_shader,
                               {{0, "Position"}, {1, "UV"}, {2, "Color"}});

    ImGui_ImplSdlGL3_CreateFontsTexture();

    return true;
}

void ImGui_ImplSdlGL3_InvalidateDeviceObjects() {
    void *ptr = ImGui::GetIO().Fonts->TexID;
    om::texture *texture = reinterpret_cast<om::texture *>(ptr);
    om::g_engine->destroy_texture(texture);

    delete g_im_gui_shader;
    g_im_gui_shader = nullptr;
}