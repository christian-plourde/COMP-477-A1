#include "Camera.h"

Camera::~Camera()
{
    delete shader;
}

Camera::Camera(const char* filepath)
{
    file_path = filepath;
    GLCall(glGenVertexArrays(1, &VAO));
    GLCall(glBindVertexArray(VAO));
    mesh_type = GL_TRIANGLES;
    camera_position = glm::vec3(0,0,1);
    glm::vec3 camera_target = glm::vec3(0,0,0); //point the camera to the origin of the world
    camera_direction = glm::normalize(camera_target - camera_position);
    glm::vec3 up = glm::vec3(0,1,0);
    right_axis = glm::normalize(glm::cross(camera_direction, up));
    up_axis = glm::normalize(glm::cross(right_axis, camera_direction));
    Model = glm::mat4(1.0f);
    camera_speed = 0.1;
}

bool Camera::load()
{
    //function to load an object into the class
    if(!LoadOBJ(file_path, indices, vertices, normals, uvs))
        return false;

    //once we have loaded the data from the file, we should set the data in our buffers

    //next we will need a buffer for the vertices, normals, and uvs
    GLCall(glGenBuffers(1, &vertex_buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), &vertices.front(), GL_STATIC_DRAW));

    GLCall(glGenBuffers(1, &normal_buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, normal_buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*normals.size(), &normals.front(), GL_STATIC_DRAW));

    GLCall(glGenBuffers(1, &texture_buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, texture_buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*uvs.size(), &uvs.front(), GL_STATIC_DRAW));

    //finally we need an EBO for the indices
    GLCall(glGenBuffers(1, &EBO));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), &indices.front(), GL_STATIC_DRAW));
    return true;
}

glm::mat4 Camera::compute_view()
{
    return glm::lookAt(camera_position, camera_position + camera_direction, up_axis);
}

glm::mat4 Camera::getView()
{
    return compute_view();
}

void Camera::move_forward()
{
    camera_position += camera_speed*camera_direction;
    //when this occurs we should set the view matrix to the inverse of the view matrix of the camera?
    for(int i = 0; i < objects->size; i++)
    {
        objects->getObject(i)->getShader()->setUniformData("view_matrix", compute_view());
        objects->getObject(i)->getShader()->setUniformData("view_position", camera_position);
    }
}

void Camera::move_backward()
{
    camera_position -= camera_speed * camera_direction;

    for (int i = 0; i < objects->size; i++)
    {
        objects->getObject(i)->getShader()->setUniformData("view_matrix", compute_view());
        objects->getObject(i)->getShader()->setUniformData("view_position", camera_position);
    }
}

void Camera::move_left()
{
    camera_position -= right_axis*camera_speed;

    for(int i = 0; i < objects->size; i++)
    {
        objects->getObject(i)->getShader()->setUniformData("view_matrix", compute_view());
        objects->getObject(i)->getShader()->setUniformData("view_position", camera_position);
    }
}

void Camera::move_right()
{
    camera_position += right_axis*camera_speed;
    for(int i = 0; i < objects->size; i++)
    {
        objects->getObject(i)->getShader()->setUniformData("view_matrix", compute_view());
        objects->getObject(i)->getShader()->setUniformData("view_position", camera_position);
    }
}

void Camera::pitch_up()
{
    camera_direction = pitch_matrix(camera_speed)*camera_direction;
    glm::normalize(camera_direction);
    up_axis = glm::normalize(glm::cross(right_axis, camera_direction));
    for(int i = 0; i < objects->size; i++)
    {
        objects->getObject(i)->getShader()->setUniformData("view_matrix", compute_view());
    }
}

void Camera::pitch_down()
{
    camera_direction = pitch_matrix(-camera_speed)*camera_direction;
    glm::normalize(camera_direction);
    up_axis = glm::normalize(glm::cross(right_axis, camera_direction));
    for(int i = 0; i < objects->size; i++)
    {
        objects->getObject(i)->getShader()->setUniformData("view_matrix", compute_view());
    }
}

void Camera::yaw_left()
{
    camera_direction = yaw_matrix(-camera_speed)*camera_direction;
    glm::normalize(camera_direction);
    right_axis = glm::normalize(glm::cross(camera_direction, up_axis));
    for(int i = 0; i < objects->size; i++)
    {
        objects->getObject(i)->getShader()->setUniformData("view_matrix", compute_view());
    }
}

void Camera::yaw_right()
{
    camera_direction = yaw_matrix(camera_speed)*camera_direction;
    glm::normalize(camera_direction);
    right_axis = glm::normalize(glm::cross(camera_direction, up_axis));
    for(int i = 0; i < objects->size; i++)
    {
        objects->getObject(i)->getShader()->setUniformData("view_matrix", compute_view());
    }
}

void Camera::roll_right()
{
    camera_direction = roll_matrix(camera_speed)*camera_direction;
    glm::normalize(camera_direction);
    right_axis = glm::normalize(glm::cross(camera_direction, up_axis));
    for(int i = 0; i < objects->size; i++)
    {
        objects->getObject(i)->getShader()->setUniformData("view_matrix", compute_view());
    }
}

void Camera::roll_left()
{
    camera_direction = roll_matrix(-camera_speed)*camera_direction;
    glm::normalize(camera_direction);
    right_axis = glm::normalize(glm::cross(camera_direction, up_axis));
    for(int i = 0; i < objects->size; i++)
    {
        objects->getObject(i)->getShader()->setUniformData("view_matrix", compute_view());
    }
}

void Camera::setProjection(float left, float right ,float bottom, float top, float near_plane, float far_plane)
{
    //Projection = glm::perspective(glm::radians(fov_degrees), (float)window_width/window_height, near_plane, far_plane);
    Projection = glm::ortho(left, right, bottom, top, near_plane, far_plane);
}

void Camera::Render()
{
    shader -> use();
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glDepthFunc(GL_LESS));
    GLCall(glDrawArrays(mesh_type, 0, vertices.size()));
    GLCall(glDisableVertexAttribArray(0));
}

void Camera::setObjects(ObjectContainer *o)
{
    objects = o;
    for(int i = 0; i < objects->size; i++)
    {
        objects->getObject(i)->getShader()->setUniformData("view_matrix", glm::inverse(compute_view()));
    }
}

glm::mat3 Camera::pitch_matrix(float degrees)
{
    return glm::mat3(glm::cos(glm::radians(degrees)), glm::sin(glm::radians(degrees)), 0, -glm::sin(glm::radians(degrees)), glm::cos(glm::radians(degrees)), 0, 0, 0, 1);
}

glm::mat3 Camera::yaw_matrix(float degrees)
{
    return glm::mat3(glm::cos(glm::radians(degrees)), 0, -glm::sin(glm::radians(degrees)), 0, 1, 0, glm::sin(glm::radians(degrees)), 0, glm::cos(glm::radians(degrees)));
}

glm::mat3 Camera::roll_matrix(float degrees)
{
    return glm::mat3(1, 0, 0, 0, glm::cos(glm::radians(degrees)), glm::sin(glm::radians(degrees)), 0, -glm::sin(glm::radians(degrees)), glm::cos(glm::radians(degrees)));
}
