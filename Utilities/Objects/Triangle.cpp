#include "Triangle.h"

Triangle::Triangle(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals)
{
    this->vertices = vertices;
    this->normals = normals;
}

Triangle::~Triangle() = default;

std::ostream& operator<<(std::ostream& os, Triangle& triangle)
{
    os << "Vertices:\n<" << triangle.vertices[0].x << ", " << triangle.vertices[0].y << ", " << triangle.vertices[0].z << ">" << std::endl;
    os << "<" << triangle.vertices[1].x << ", " << triangle.vertices[1].y << ", " << triangle.vertices[1].z << ">" << std::endl;
    os << "<" << triangle.vertices[2].x << ", " << triangle.vertices[2].y << ", " << triangle.vertices[2].z << ">" <<std::endl;
    os << "Normals:\n<" << triangle.normals[0].x << ", " << triangle.normals[0].y << ", " << triangle.normals[0].z << ">" << std::endl;
    os << "<" << triangle.normals[1].x << ", " << triangle.normals[1].y << ", " << triangle.normals[1].z << ">" << std::endl;
    os << "<" << triangle.normals[2].x << ", " << triangle.normals[2].y << ", " << triangle.normals[2].z << ">" <<std::endl;
    return os;
}