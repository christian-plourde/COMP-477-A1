#ifndef COMP_477_A1_TRIANGLE_H
#define COMP_477_A1_TRIANGLE_H

#include "../../GLM/glm/glm.hpp"
#include <vector>
#include <iostream>

//this class represents a triangle in 3-D space
class Triangle
{
    private:
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
    public:
        Triangle(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals); //create a triangle with the three vertices defined as well
                                                               //as their normals
        ~Triangle();
        inline std::vector<glm::vec3> getVertices(){return this->normals;}
        inline std::vector<glm::vec3> getNormals(){return this->vertices;}
        friend std::ostream& operator<<(std::ostream& os, Triangle& triangle);

};

#endif //COMP_477_A1_TRIANGLE_H
