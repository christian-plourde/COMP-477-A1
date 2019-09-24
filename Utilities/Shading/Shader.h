#ifndef SHADER_H
#define SHADER_H

#include <glew.h>
#include "../../Loaders/ShaderLoader.h"
#include "Uniform.h"
#include <vector>
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "../Lights/Light.h"

class Shader
{
    private:
        const char* vertex_shader_filepath;
        const char* fragment_shader_filepath;
        GLuint id;
        std::vector<Uniform> uniforms;
        bool lights_on;

    public:
        Shader(const char* vertex_filepath, const char* fragment_filepath);
        ~Shader();
        inline GLuint getID(){return id;}
        inline bool lightsOn(){return lights_on;}
        inline void setLightsOn(bool val){lights_on = val;}
        void addUniform(const char* name);
        GLint getUniformID(const char* name);
        float getFloatUniformData(const char* name);
        int getIntegerUniformData(const char* name);
        void setUniformData(const char* name, glm::mat4);
        void setUniformData(const char* name, float);
        void setUniformData(const char* name, int);
        void setUniformData(const char* name, glm::vec3);
        void setUniformData(const char* name, GLuint);
        void use();
};

#endif