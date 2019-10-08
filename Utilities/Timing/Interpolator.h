#ifndef COMP_477_A1_PROBLEM_1_INTERPOLATOR_H
#define COMP_477_A1_PROBLEM_1_INTERPOLATOR_H

#include <vector>
#include "glm.hpp"
#include "matrix.hpp"

void print_mat4(glm::mat4);
void print_vec3(glm::vec3);

class Interpolator
{
    private:
        glm::mat4 catmull_rom_basis;
        glm::mat4 bezier_basis;
        float s; //tension parameter for catmull rom

    public:
        Interpolator();
        glm::vec3 calculate_catmull_rom(glm::vec3, glm::vec3, glm::vec3, glm::vec3, float u); //u is the parameter that indicates where we are on the curve (between 0 and 1)
        glm::vec3 calculate_bezier(glm::vec3, glm::vec3, glm::vec3, glm::vec3, float u); //u is the parameter for bezier (betwen 0 and 1)
};

#endif //COMP_477_A1_PROBLEM_1_INTERPOLATOR_H
