#include "Shader.h"
#include <iostream>
#include <string>

Shader::Shader(const char*vertex_filepath, const char *fragment_filepath)
{
    this -> vertex_shader_filepath = vertex_filepath;
    this -> fragment_shader_filepath = fragment_filepath;
    id = LoadShaders(vertex_filepath, fragment_filepath);
    lights_on = false;
}

Shader::~Shader(){}

void Shader::addUniform(const char *name)
{
    this -> use();
    Uniform uniform(name); //create a new uniform
    //we need to get its id in the shader
    uniform.setID(glGetUniformLocation(id, uniform.getName()));
    uniforms.push_back(uniform);
}

GLint Shader::getUniformID(const char *name)
{
    for(int i = 0; i < uniforms.size(); i++)
    {
        if(std::strcmp(name, uniforms[i].getName()) == 0)
            return uniforms[i].getID();
    }

    return -1;
}

float Shader::getFloatUniformData(const char *name)
{
    this -> use();
    //method to get the data in a float uniform
    GLint uniform_id = getUniformID(name);
    float result;
    glGetUniformfv(id, uniform_id, &result);
    return result;
}

int Shader::getIntegerUniformData(const char *name)
{
    this -> use();
    GLint uniform_id = getUniformID(name);
    int result;
    glGetUniformiv(id, uniform_id, &result);
    return result;
}

void Shader::setUniformData(const char *name, glm::mat4 matrix)
{
    this -> use();
    GLint id = getUniformID(name);
    glUniformMatrix4fv(id, 1, GL_FALSE, &(matrix[0][0]));
}

void Shader::setUniformData(const char *name, float value)
{
    this -> use();
    GLint id = getUniformID(name);
    glUniform1f(id, value);
}

void Shader::setUniformData(const char *name, int value)
{
    this -> use();
    GLint id = getUniformID(name);
    glUniform1i(id, value);
}

void Shader::setUniformData(const char *name, GLuint value)
{
    this -> use();
    GLint id = getUniformID(name);
    glUniform1i(id, value);
}

void Shader::setUniformData(const char *name, glm::vec3 vector)
{
    this -> use();
    GLint id = getUniformID(name);
    glUniform3fv(id, 1, glm::value_ptr(vector));
}

void Shader::use()
{
    glUseProgram(id);
}

