#include "MVP.h"
#include "gtc/matrix_transform.hpp"

MVP::MVP()
{
    Model = glm::mat4(1.0f);
    view_eye = glm::vec3(50,-30,10);
    view_direction = glm::vec3(0,0,0);
    view_up = glm::vec3(0, 0, 1);
    View = glm::lookAt(view_eye,view_direction, view_up);
    Projection = glm::mat4(1.0f);
}

MVP::~MVP()
{

}

void MVP::setModel(glm::mat4 model)
{
    Model = model;
}

void MVP::setView(glm::vec3 eye, glm::vec3 point, glm::vec3 up_vector)
{
    view_eye = eye;
    view_direction = point;
    view_up = up_vector;
    View = glm::lookAt(eye,point,up_vector);
}

void MVP::setView(glm::mat4 newView)
{
    //view_eye = glm::vec3(newView[3][0], newView[3][1], newView[3][2]);
    //view_direction = glm::vec3(-newView[2][0], -newView[2][1], -newView[2][2]);
    //view_up = glm::vec3(newView[1][0], newView[1][1], newView[1][2]);
    View = newView;
}

void MVP::setViewEye(glm::vec3 e)
{
    view_eye = e;
    View = glm::lookAt(view_eye,view_direction,view_up);
}

void MVP::setViewDirection(glm::vec3 dir)
{
    view_direction = dir;
    View = glm::lookAt(view_eye,view_direction,view_up);
}

void MVP::setViewUp(glm::vec3 up)
{
    view_up = up;
    View = glm::lookAt(view_eye,view_direction,view_up);
}

void MVP::setProjection(float fov_degrees, int window_width, int window_height, float near_plane, float far_plane)
{
    Projection = glm::perspective(glm::radians(fov_degrees), (float)window_width/window_height, near_plane, far_plane);
}

glm::mat4 MVP::getMVP()
{
    return Projection*View*Model;
}

