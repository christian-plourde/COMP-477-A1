#include "BoundingBox.h"

BoundingBox::BoundingBox(){}

BoundingBox::~BoundingBox(){}

void BoundingBox::setVertices(std::vector<glm::vec3>* vertices)
{
    this->vertices.clear();

    max_x = (*vertices)[0].x;
    max_y = (*vertices)[0].y;
    max_z = (*vertices)[0].z;
    min_x = (*vertices)[0].x;
    min_y = (*vertices)[0].y;
    min_z = (*vertices)[0].z;

    for(int i = 0; i < (*vertices).size(); i++)
    {
        if((*vertices)[i].x < min_x)
            min_x = (*vertices)[i].x;

        if((*vertices)[i].y < min_y)
            min_y = (*vertices)[i].y;

        if((*vertices)[i].z < min_z)
            min_z = (*vertices)[i].z;

        if((*vertices)[i].x > max_x)
            max_x = (*vertices)[i].x;

        if((*vertices)[i].y > max_y)
            max_y = (*vertices)[i].y;

        if((*vertices)[i].z > max_z)
            max_z = (*vertices)[i].z;
    }

    this->vertices.push_back(glm::vec3(max_x + mvp->getModel()[3].x, max_y + mvp->getModel()[3].y, max_z + mvp->getModel()[3].z));
    this->vertices.push_back(glm::vec3(min_x + mvp->getModel()[3].x, max_y + mvp->getModel()[3].y, max_z + mvp->getModel()[3].z));
    this->vertices.push_back(glm::vec3(max_x + mvp->getModel()[3].x, max_y + mvp->getModel()[3].y, min_z + mvp->getModel()[3].z));
    this->vertices.push_back(glm::vec3(min_x + mvp->getModel()[3].x, max_y + mvp->getModel()[3].y, min_z + mvp->getModel()[3].z));
    this->vertices.push_back(glm::vec3(max_x + mvp->getModel()[3].x, min_y + mvp->getModel()[3].y, max_z + mvp->getModel()[3].z));
    this->vertices.push_back(glm::vec3(min_x + mvp->getModel()[3].x, min_y + mvp->getModel()[3].y, max_z + mvp->getModel()[3].z));
    this->vertices.push_back(glm::vec3(max_x + mvp->getModel()[3].x, min_y + mvp->getModel()[3].y, min_z + mvp->getModel()[3].z));
    this->vertices.push_back(glm::vec3(min_x + mvp->getModel()[3].x, min_y + mvp->getModel()[3].y, min_z + mvp->getModel()[3].z));
}

std::ostream& operator<<(std::ostream& os, BoundingBox& box)
{
    for(int i = 0; i < box.vertices.size(); i++)
    {
        os << "<" << box.vertices[i].x << ", " << box.vertices[i].y << ", " << box.vertices[i].z << ">" << std::endl;
    }

    return os;
}