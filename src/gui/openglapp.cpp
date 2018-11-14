
#include <iostream>

#include "glad/glad.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "openglapp.h"

OpenGLApp::OpenGLApp()
{
    if (!glfwInit()) {
        throw std::runtime_error("Cannot init GLFW.");
    }
}

OpenGLApp::~OpenGLApp()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

void MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message,
                     const void* userParam )
{
  std::cout << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "OpenGl: ") << message << std::endl;
  if (type == GL_DEBUG_TYPE_ERROR) {
      throw std::runtime_error("OpenGL error");
  }
}

void OpenGLApp::show()
{
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode mWindow and its OpenGL context */
    mWindow = glfwCreateWindow(1024, 768, "Forces Simulation", NULL, NULL);
    if (!mWindow) {
        throw std::runtime_error("Cannot create mWindow.");
    }

    /* Make the mWindow's context current */
    glfwMakeContextCurrent(mWindow);

    glfwSetWindowUserPointer(mWindow, this);
    glfwSetCursorPosCallback(mWindow, cursor_pos_callback);
    glfwSetMouseButtonCallback(mWindow, mouse_button_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw std::runtime_error("Failed to initialize GLAD");
    }
    if (!gladLoadGL())
    {
        throw std::runtime_error("gladLoadGL() failed");
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    std::cout << "GL version: " << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
    ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup style
    ImGui::StyleColorsDark();

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'misc/fonts/README.txt' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    onSetup();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(mWindow))
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        onDraw();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(mWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

void OpenGLApp::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    auto app = static_cast<OpenGLApp *>(glfwGetWindowUserPointer(window));
    if (app->mIsDragging) {
        app->onDrag(xpos, ypos);
    } else {
        app->onMouseMove(xpos, ypos);
    }
}

void OpenGLApp::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    auto app = static_cast<OpenGLApp *>(glfwGetWindowUserPointer(window));
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        app->mMousePressedTime = std::chrono::steady_clock::now();
        app->mMousePressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        app->mMousePressed = false;
        if (app->mIsDragging) {
            app->onDragEnd(xpos, ypos);
            app->mIsDragging = false;
        } else {
            app->onMouseRelease(xpos, ypos);
        }
    }
}

void OpenGLApp::onSetup()
{

}

void OpenGLApp::onDraw()
{

}

void OpenGLApp::onMouseMove(double xpos, double ypos)
{

}

void OpenGLApp::onMousePress(double xpos, double ypos)
{

}

void OpenGLApp::onMouseRelease(double xpos, double ypos)
{

}

void OpenGLApp::onDragStart(double xpos, double ypos)
{

}

void OpenGLApp::onDrag(double xpos, double ypos)
{

}

void OpenGLApp::onDragEnd(double xpos, double ypos)
{

}
