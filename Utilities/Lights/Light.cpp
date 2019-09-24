#include "Light.h"

//create a new light centered at origin, color = white
Light::Light() : position(glm::vec3(0,0,0)), color(glm::vec3(1,1,1)){}

Light::Light(glm::vec3 pos, glm::vec3 col) : position(pos), color(col){}

Light::Light(float x, float y, float z, float red, float green, float blue) :
position(glm::vec3(x,y,z)), color(glm::vec3(red, green, blue))
{}

Light::~Light()
{

}

//This method will add a light to a program by means of a uniform
void Light::addToProgram(GLuint programID, const char* light_pos_uniform, const char* light_color_uniform)
{
    glUniform3fv(glGetUniformLocation(programID, light_pos_uniform), 1, glm::value_ptr(position));
    glUniform3fv(glGetUniformLocation(programID, light_color_uniform), 1, glm::value_ptr(color));
}

glm::vec3 Light::getPosition()
{
    return position;
}

glm::vec3 Light::getColor()
{
    return color;
}

std::ostream& operator<<(std::ostream& os, const Light& light)
{
    os << "Position: <" << light.position.x << "," << light.position.y << "," << light.position.z << ">\n";
    os << "Color: <" << light.color.x << "," << light.color.y << "," << light.color.z << ">\n";
    return os;
}
