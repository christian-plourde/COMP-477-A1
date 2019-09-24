#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include <glew.h>
#include <iostream>

#ifndef COMP_371_A3_LIGHT_H
#define COMP_371_A3_LIGHT_H

class Light
{
    private:
        glm::vec3 position;
        glm::vec3 color;
    public:
        Light();
        Light(glm::vec3, glm::vec3);
        Light(float, float, float, float, float, float);
        ~Light();
        void addToProgram(GLuint, const char*, const char*);
        glm::vec3 getPosition();
        glm::vec3 getColor();
        friend std::ostream& operator<<(std::ostream&, const Light&);
};

#endif
