#ifndef OPENGLAPP_H
#define OPENGLAPP_H

#include <iostream>
#include <string>
#include <chrono>
#include <memory>

#include "GLFW/glfw3.h"

class Demo;

class OpenGLApp
{
public:
    OpenGLApp();
    virtual ~OpenGLApp();

    virtual void show();

    virtual void onSetup();
    virtual void onDraw();
    virtual void onMouseMove(double xpos, double ypos);
    virtual void onMousePress(double xpos, double ypos);
    virtual void onMouseRelease(double xpos, double ypos);
    virtual void onDragStart(double xpos, double ypos);
    virtual void onDrag(double xpos, double ypos);
    virtual void onDragEnd(double xpos, double ypos);

private:
    static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    GLFWwindow* mWindow { nullptr };
    bool mIsDragging { false };
    bool mMousePressed { false };
    std::chrono::time_point<std::chrono::steady_clock> mMousePressedTime { std::chrono::steady_clock::now() };
};

#endif // OPENGLAPP_H
