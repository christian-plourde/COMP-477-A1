#include "DepthMapLight.h"

DepthMapLight::DepthMapLight()
{
    near_plane = 1.0f;
    far_plane = 10000.0f;
    projection = glm::perspective(glm::radians(85.0f), 1.0f, near_plane, far_plane);
    eye = glm::vec3(0, 20, 25);
    looking_at = glm::vec3(0,-10,-10);
    up_vector = glm::vec3(0,1,0);
    view = glm::lookAt(eye, looking_at, up_vector);
    model = glm::mat4(1.0);
    CalcLightMatrix();
}

DepthMapLight::~DepthMapLight() {}

void DepthMapLight::CalcLightMatrix()
{
    light_matrix = projection*view*model;
}

void DepthMapLight::setProjection(float fov_degrees, int window_width, int window_height, float near_plane, float far_plane)
{
    projection = glm::perspective(glm::radians(fov_degrees), (float)window_width/window_height, near_plane, far_plane);
    CalcLightMatrix();
}

