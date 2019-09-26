#include <iostream>
#include <string>
#include <sstream>
#include <glew.h>
#include <GLFW/glfw3.h>
#include "GLM/glm/matrix.hpp"
#include "GLM/glm/gtc/matrix_transform.hpp"
#include "GLM/glm/gtc/type_ptr.hpp"
#include "Loaders/ShaderLoader.h"
#include "Loaders/ObjectLoader.h"
#include "Controls/KeyboardControls.h"
#include "Utilities/Lights/Light.h"
#include "Utilities/Window/Window.h"
#include "Utilities/Objects/Object.h"
#include "Utilities/ErrorHandling/ErrorHandlingFunctions.h"
#include "Utilities/Objects/ObjectContainer.h"
#include "Utilities/ShadowMapping/DepthMap.h"
#include "Utilities/Lights/SpotLight.h"
#include "Utilities/Camera/Camera.h"

Window* myWindow; //the glfw window
ObjectContainer* objects;
Camera* camera;

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    /*
     * This defines what happens when the escape key is pressed. In our case, we would like the escape key to close
     * the currently used window
     */
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    //here we define what occurs if specific keys are pressed
    //the functions are defined in the keyboard controls file, we are simply calling them based on
    //which key is pressed

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera->move_forward();
        //key_press_w(objects);
    }


    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera ->move_backward();
        //key_press_s(objects);
    }


    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera -> move_left();
        //key_press_a(objects);
    }


    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera -> move_right();
        //key_press_d(objects);
    }


    if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        key_press_o(objects);

    if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        key_press_p(objects);

    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        camera->yaw_left();
        //key_press_left_arrow(objects);
    }

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        camera->yaw_right();
        //key_press_right_arrow(objects);
    }

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        camera->pitch_up();
        //key_press_up_arrow(objects);
    }


    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        camera->pitch_down();
        //key_press_down_arrow(objects);
    }

    if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        camera->roll_right();
    }

    if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        camera->roll_left();
    if(glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
        key_press_b(objects);

    if(glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        key_press_n(objects);

    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        key_press_e(objects);


    if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        key_press_j(objects);

    if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        key_press_l(objects);

    if(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        key_press_i(objects);

    if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        key_press_k(objects);

    if(glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
        key_press_pg_up(objects);

    if(glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
        key_press_pg_down(objects);
}

int main()
{
    myWindow = new Window();
    myWindow -> set_keyboard_callback(keyboard_callback);
    myWindow -> setBackColor(0.8, 0.8, 0.8);
    objects = new ObjectContainer();

    camera = new Camera("../ObjectFiles/cube.obj");
    camera->setPosition(glm::vec3(0, 0, 10));
    camera->load();
    camera->setProjection(-1000.0f, 1000.0f, -1000.0f, 1000.0f, 0.1f, 10000.0f);
    camera->setSpeed(1.0f);
    Shader* camera_shader = new Shader("../Shaders/CameraVertexShader.glsl", "../Shaders/CameraFragmentShader.glsl");
    camera->setShader(camera_shader);
    camera_shader->addUniform("model_matrix");
    camera_shader->setUniformData("model_matrix", camera->getModel());
    camera_shader->addUniform("view_matrix");
    camera_shader->setUniformData("view_matrix", camera->getView());
    camera_shader->addUniform("projection_matrix");
    camera_shader->setUniformData("projection_matrix", camera->getProjection());

    Object cube("../ObjectFiles/cube.obj");
    cube.load();
    std::cout << cube.getTriangles().size() << std::endl;
    MVP cubeMVP;
    cubeMVP.setProjection(60.0f, myWindow->getWidth(), myWindow->getHeight(), 0.1f, 10000.0f);
    cube.setMVP(&cubeMVP);
    cube.setScreenWidth(myWindow->getWidth());
    cube.setScreenHeight(myWindow->getHeight());

    Object sphere("../ObjectFiles/sphere.obj");
    sphere.load();
    MVP sphereMVP;
    sphereMVP.setProjection(60.0f, myWindow->getWidth(), myWindow->getHeight(), 0.1f, 10000.0f);
    sphere.setMVP(&sphereMVP);
    sphere.setScreenWidth(myWindow->getWidth());
    sphere.setScreenHeight(myWindow->getHeight());

    Shader* cubeshader = new Shader("../Shaders/BasicVertexShader.glsl", "../Shaders/BasicFragmentShader.glsl");
    cube.setShader(cubeshader);
    cubeshader -> addUniform("view_matrix");
    //cubeshader -> setUniformData("view_matrix", cube.getMVP() -> getView());
    cubeshader -> setUniformData("view_matrix", camera->getView());
    cubeshader -> addUniform("model_matrix");
    cubeshader -> setUniformData("model_matrix", cube.getMVP() -> getModel());
    cubeshader -> addUniform("projection_matrix");
    cubeshader -> setUniformData("projection_matrix", cube.getMVP() -> getProjection());
    cubeshader -> addUniform("view_position");
    cubeshader -> setUniformData("view_position", camera->getPosition());
    Light light1(0, 20, 10, 0, 0, 1);
    cubeshader -> addUniform("light_position_1");
    cubeshader -> addUniform("light_color_1");
    cubeshader -> setUniformData("light_position_1", light1.getPosition());
    cubeshader -> setUniformData("light_color_1", light1.getColor());

    Shader* sphereShader = new Shader("../Shaders/SphereVertexShader.glsl", "../Shaders/SphereFragmentShader.glsl");
    sphere.setShader(sphereShader);
    sphere.setAsStatic();
    sphereShader -> addUniform("view_matrix");
    sphereShader -> setUniformData("view_matrix", camera->getView());
    sphereShader -> addUniform("model_matrix");
    sphereShader -> setUniformData("model_matrix", sphere.getMVP() -> getModel());
    sphereShader -> addUniform("projection_matrix");
    sphereShader -> setUniformData("projection_matrix", sphere.getMVP() -> getProjection());
    sphereShader -> addUniform("view_position");
    sphereShader -> setUniformData("view_position", camera->getPosition());
    Light sphereLight(0, 20, 10, 1, 0, 0);
    sphereShader -> addUniform("light_position_1");
    sphereShader -> addUniform("light_color_1");
    sphereShader -> setUniformData("light_position_1", sphereLight.getPosition());
    sphereShader -> setUniformData("light_color_1", sphereLight.getColor());

    objects->addObject(&cube);
    objects->addObject(&sphere);

    camera->setObjects(objects);

    //every frame we need to move the sphere
    glm::vec3 sphere_move_direction(0.001, 0.001, 0);

    while (!glfwWindowShouldClose(myWindow -> getHandle()))
    {
        myWindow->PrepareDraw();
        cube.setViewPort();
        camera->Render();
        cube.Draw(true, true, true);
        sphere.Draw(true, true, false);
        myWindow->EndDraw();

        //this will move the sphere in the direction indicated by sphere_move_direction
        sphere.getMVP()->setModel(glm::translate(sphere.getMVP()->getModel(), sphere_move_direction));
        sphere.getShader() -> setUniformData("model_matrix", sphere.getMVP()->getModel());

    }


    delete objects;
    delete camera;
    delete myWindow;

    glfwTerminate();

    return 0;
}