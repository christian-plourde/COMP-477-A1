#include "Window.h"

Window::Window() : width(800), height(800), title("Window"), back_color(glm::vec3(0,0,0))
{
    window_handle = initHandle();
    glClearColor(back_color.x, back_color.y, back_color.z, 1);
    glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
    glewExperimental = GL_TRUE;
}

Window::Window(int width, int height, const char* title) : width(800), height(800), back_color(glm::vec3(0,0,0))
{
    window_handle = initHandle();
    glClearColor(back_color.x, back_color.y, back_color.z, 1);
    glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
    glewExperimental = GL_TRUE;
}

Window::~Window()
{
}

void Window::setBackColor(float red, float green, float blue)
{
    back_color = glm::vec3(red, green, blue);
    glClearColor(back_color.x, back_color.y, back_color.z, 1);
}

GLFWwindow* Window::initHandle()
{
    // Initialize the library
    if (!glfwInit())
        return nullptr;

    window_handle = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window_handle)
    {
        glfwTerminate();
        return nullptr;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window_handle);
    glClearColor(back_color.x, back_color.y, back_color.z, 1); //makes the background color of the window light gray
    //we should also set the keyboard input callback method
    glfwWindowHint(GLFW_DOUBLEBUFFER, 1);

    glewExperimental = GL_TRUE;

    if (GLEW_OK != glewInit())
    {
        return nullptr;
    }

    return window_handle;
}

void Window::set_keyboard_callback(GLFWkeyfun function)
{
    glfwSetKeyCallback(window_handle, function);
}

void Window::PrepareDraw()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Window::EndDraw()
{
    GLCall(glfwSwapBuffers(window_handle));

    GLCall(glfwPollEvents());
}




