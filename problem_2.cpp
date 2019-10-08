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
#include "Utilities/Timing/Timestep.h"
#include "Utilities/Timing/GradualTranslation.h"
#include "Utilities/Timing/Interpolator.h"

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
    //choose part of problem to execute
    bool ready = false;
    char part;

    while(!ready)
    {
        std::cout << "Please choose part of problem to execute (a/b/c/d): ";
        std::cin >> part;

        if(!(part == 'a' || part == 'b' || part == 'c' || part == 'd'))
        {
            std::cout << "Not a valid choice." << std::endl;
            continue;
        }
        ready = true;
    }


    myWindow = new Window();
    myWindow -> set_keyboard_callback(keyboard_callback);
    myWindow -> setBackColor(0.8, 0.8, 0.8);
    objects = new ObjectContainer();

    camera = new Camera("../ObjectFiles/cube.obj");
    camera->setPosition(glm::vec3(0, 0, 20));
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

    //setting up sphere
    Object sphere("../ObjectFiles/sphere.obj");
    MVP sphereMVP;
    sphereMVP.setProjection(60.0f, myWindow->getWidth(), myWindow->getHeight(), 0.1f, 10000.0f);
    sphere.setMVP(&sphereMVP);
    sphere.setScreenWidth(myWindow->getWidth());
    sphere.setScreenHeight(myWindow->getHeight());
    sphere.scale(0.02);
    sphere.load();

    Shader* sphereShader = new Shader("../Shaders/SphereVertexShader.glsl", "../Shaders/SphereFragmentShader.glsl");
    sphere.setShader(sphereShader);
    sphere.setAsStatic(); //will not be affected by motion controls
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

    objects->addObject(&sphere);

    camera->setObjects(objects);

    /********************************* SETUP SETTINGS BASED ON PART OF PROBLEM ***************************/

    if(part == 'a')
    {
        std::vector<glm::vec3> point_trajectory;
        int point_track = 0;
        point_trajectory.push_back(glm::vec3(0,0,0));
        point_trajectory.push_back(glm::vec3(1, 3, -1));
        point_trajectory.push_back(glm::vec3(4, 0, 3));
        point_trajectory.push_back(glm::vec3(6, 4, 4));
        point_trajectory.push_back(glm::vec3(10, 2, 5));
        point_trajectory.push_back(glm::vec3(0, 0, 0));
        GradualTranslation gradualTranslation(5, point_trajectory[0]);
        gradualTranslation.setObject(&sphere);

        while (!glfwWindowShouldClose(myWindow -> getHandle()))
        {
                if(!(point_track == point_trajectory.size()))
                    if(!gradualTranslation.isComplete())
                        gradualTranslation.step_linear();

                    else
                    {
                        point_track++;
                        gradualTranslation.reset();
                        gradualTranslation.setEnd(point_trajectory[point_track]);
                    }

            myWindow->PrepareDraw();
            sphere.setViewPort();
            camera->Render();
            sphere.Draw(true, true, false);
            myWindow->EndDraw();
        }
    }

    if(part == 'b')
    {
        std::vector<glm::vec3> point_trajectory;
        point_trajectory.push_back(glm::vec3(0, 0, 0));
        point_trajectory.push_back(glm::vec3(0,0,0));
        point_trajectory.push_back(glm::vec3(1, 3, -1));
        point_trajectory.push_back(glm::vec3(4, 0, 3));
        point_trajectory.push_back(glm::vec3(6, 4, 4));
        point_trajectory.push_back(glm::vec3(10, 2, 5));
        point_trajectory.push_back(glm::vec3(0, 0, 0));
        point_trajectory.push_back(glm::vec3(0, 0, 0));

        Interpolator interpolator;
        float u = 0;
        int start_index = 0;
        int segment_tracker = 1;

        while (!glfwWindowShouldClose(myWindow -> getHandle()))
        {
            if(segment_tracker <= point_trajectory.size() - 2)
            {
                sphere.move_to(interpolator.calculate_catmull_rom(point_trajectory[start_index],
                        point_trajectory[start_index+1], point_trajectory[start_index+2], point_trajectory[start_index+3]
                        , u));

                if(u < 1)
                    u+=0.0001;

                else
                {
                    //otherwise we should reset u and recalculate the spline
                    u = 0;
                    start_index = start_index + 1;
                    segment_tracker++;
                }
            }


            myWindow->PrepareDraw();
            sphere.setViewPort();
            camera->Render();
            sphere.Draw(true, true, false);
            myWindow->EndDraw();
        }
    }

    if(part == 'c')
    {
        std::vector<glm::vec3> point_trajectory;
        point_trajectory.push_back(glm::vec3(0, 0, 0));
        point_trajectory.push_back(glm::vec3(0,0,0));
        point_trajectory.push_back(glm::vec3(1, 3, -1));
        point_trajectory.push_back(glm::vec3(4, 0, 3));
        point_trajectory.push_back(glm::vec3(6, 4, 4));
        point_trajectory.push_back(glm::vec3(10, 2, 5));
        point_trajectory.push_back(glm::vec3(0, 0, 0));
        point_trajectory.push_back(glm::vec3(0, 0, 0));

        Interpolator interpolator;
        float u = 0;
        int start_index = 0;
        int segment_tracker = 1;

        while (!glfwWindowShouldClose(myWindow -> getHandle()))
        {
            if(segment_tracker <= point_trajectory.size() - 2)
            {
                sphere.move_to(interpolator.calculate_bezier(point_trajectory[start_index],
                                                                  point_trajectory[start_index+1], point_trajectory[start_index+2], point_trajectory[start_index+3]
                        , u));

                if(u < 1)
                    u+=0.0001;

                else
                {
                    //otherwise we should reset u and recalculate the spline
                    u = 0;
                    start_index = start_index + 3;
                    segment_tracker++;
                }
            }

            myWindow->PrepareDraw();
            sphere.setViewPort();
            camera->Render();
            sphere.Draw(true, true, false);
            myWindow->EndDraw();
        }
    }

    if(part == 'd')
    {
        std::vector<glm::vec3> point_trajectory;
        point_trajectory.push_back(glm::vec3(0, 0, 0));
        point_trajectory.push_back(glm::vec3(0,0,0));
        point_trajectory.push_back(glm::vec3(1, 3, -1));
        point_trajectory.push_back(glm::vec3(4, 0, 3));
        point_trajectory.push_back(glm::vec3(6, 4, 4));
        point_trajectory.push_back(glm::vec3(10, 2, 5));
        point_trajectory.push_back(glm::vec3(0, 0, 0));
        point_trajectory.push_back(glm::vec3(0, 0, 0));

        Interpolator interpolator;
        float u = 0;
        int start_index = 0;
        int segment_tracker = 1;

        while (!glfwWindowShouldClose(myWindow -> getHandle()))
        {
            if(segment_tracker <= point_trajectory.size() - 2)
            {
                sphere.move_to(interpolator.calculate_catmull_rom(point_trajectory[start_index],
                                                                  point_trajectory[start_index+1], point_trajectory[start_index+2], point_trajectory[start_index+3]
                        , u));

                if(u < 1)
                {
                    //extra code for ease in/out
                    if(u < 0.02)
                        u+=0.0001;
                    else if(u > 0.98)
                        u+=0.0001;
                    else
                        u += 0.0002;
                }

                else
                {
                    //otherwise we should reset u and recalculate the spline
                    u = 0;
                    start_index = start_index + 1;
                    segment_tracker++;
                }
            }


            myWindow->PrepareDraw();
            sphere.setViewPort();
            camera->Render();
            sphere.Draw(true, true, false);
            myWindow->EndDraw();
        }
    }


    delete objects;
    delete camera;
    delete myWindow;

    glfwTerminate();

    return 0;
}

