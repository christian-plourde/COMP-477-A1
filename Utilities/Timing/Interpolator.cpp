#include "Interpolator.h"
#include <iostream>

Interpolator::Interpolator()
{
    s = 0.5;
    //instantiate the basis matrix for catmull rom
    catmull_rom_basis[0][0] = -s;
    catmull_rom_basis[0][1] = 2-s;
    catmull_rom_basis[0][2] = s-2;
    catmull_rom_basis[0][3] = s;
    catmull_rom_basis[1][0] = 2*s;
    catmull_rom_basis[1][1] = s-3;
    catmull_rom_basis[1][2] = 3-2*s;
    catmull_rom_basis[1][3] = -s;
    catmull_rom_basis[2][0] = -s;
    catmull_rom_basis[2][1] = 0;
    catmull_rom_basis[2][2] = s;
    catmull_rom_basis[2][3] = 0;
    catmull_rom_basis[3][0] = 0;
    catmull_rom_basis[3][1] = 1;
    catmull_rom_basis[3][2] = 0;
    catmull_rom_basis[3][3] = 0;

    //instantiate  the basis for bezier
    bezier_basis[0][0] = -1;
    bezier_basis[0][1] = 3;
    bezier_basis[0][2] = -3;
    bezier_basis[0][3] = 1;
    bezier_basis[1][0] = 3;
    bezier_basis[1][1] = -6;
    bezier_basis[1][2] = 3;
    bezier_basis[1][3] = 0;
    bezier_basis[2][0] = -3;
    bezier_basis[2][1] = 3;
    bezier_basis[2][2] = 0;
    bezier_basis[2][3] = 0;
    bezier_basis[3][0] = 1;
    bezier_basis[3][1] = 0;
    bezier_basis[3][2] = 0;
    bezier_basis[3][3] = 0;
}

glm::vec3 Interpolator::calculate_catmull_rom(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float u)
{
    glm::vec4 t = glm::mat4(p0.x, p0.y, p0.z, 0,
               p1.x, p1.y, p1.z, 0,
                p2.x, p2.y, p2.z, 0,
                p3.x, p3.y, p3.z, 0
                )*catmull_rom_basis*glm::vec4(pow(u, 3), pow(u, 2), u, 1);

    return glm::vec3(t);
}

glm::vec3 Interpolator::calculate_bezier(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float u)
{
    glm::vec4 t = glm::mat4(p0.x, p0.y, p0.z, 0,
                            p1.x, p1.y, p1.z, 0,
                            p2.x, p2.y, p2.z, 0,
                            p3.x, p3.y, p3.z, 0
    )*bezier_basis*glm::vec4(pow(u, 3), pow(u, 2), u, 1);

    return glm::vec3(t);
}


void print_mat4(glm::mat4 matrix)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void print_vec3(glm::vec3 vector)
{
    for(int i = 0; i < 3; i++)
    {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}


