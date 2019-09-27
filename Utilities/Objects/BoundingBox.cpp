#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
    scale_factor = 1;
}

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

    max_x *= scale_factor;
    max_y *= scale_factor;
    max_z *= scale_factor;
    min_x *= scale_factor;
    min_y *= scale_factor;
    min_z *= scale_factor;

    this->vertices.push_back(glm::vec3(max_x + mvp->getModel()[3].x, max_y + mvp->getModel()[3].y, max_z + mvp->getModel()[3].z));
    this->vertices.push_back(glm::vec3(min_x + mvp->getModel()[3].x, max_y + mvp->getModel()[3].y, max_z + mvp->getModel()[3].z));
    this->vertices.push_back(glm::vec3(max_x + mvp->getModel()[3].x, max_y + mvp->getModel()[3].y, min_z + mvp->getModel()[3].z));
    this->vertices.push_back(glm::vec3(min_x + mvp->getModel()[3].x, max_y + mvp->getModel()[3].y, min_z + mvp->getModel()[3].z));
    this->vertices.push_back(glm::vec3(max_x + mvp->getModel()[3].x, min_y + mvp->getModel()[3].y, max_z + mvp->getModel()[3].z));
    this->vertices.push_back(glm::vec3(min_x + mvp->getModel()[3].x, min_y + mvp->getModel()[3].y, max_z + mvp->getModel()[3].z));
    this->vertices.push_back(glm::vec3(max_x + mvp->getModel()[3].x, min_y + mvp->getModel()[3].y, min_z + mvp->getModel()[3].z));
    this->vertices.push_back(glm::vec3(min_x + mvp->getModel()[3].x, min_y + mvp->getModel()[3].y, min_z + mvp->getModel()[3].z));

    max_x = max_x + mvp->getModel()[3].x;
    max_y = max_y + mvp->getModel()[3].y;
    max_z = max_z + mvp->getModel()[3].z;
    min_x = min_x + mvp->getModel()[3].x;
    min_y = min_y + mvp->getModel()[3].y;
    min_z = min_z + mvp->getModel()[3].z;
}

std::ostream& operator<<(std::ostream& os, BoundingBox& box)
{
    for(int i = 0; i < box.vertices.size(); i++)
    {
        os << "<" << box.vertices[i].x << ", " << box.vertices[i].y << ", " << box.vertices[i].z << ">" << std::endl;
    }

    return os;
}

bool BoundingBox::collides_with(BoundingBox &other_box, CollisionPlane& plane)
{
    bool collide_x = false;
    bool collide_y = false;
    bool collide_z = false;

    if(min_x < other_box.min_x && max_x > other_box.min_x)
    {
        plane = NEGATIVE_X;
        collide_x = true;
    }

    if(min_x < other_box.max_x && max_x > other_box.max_x)
    {
        plane = POSITIVE_X;
        collide_x = true;
    }

    if(min_y <= other_box.min_y && max_y >= other_box.min_y)
    {
        plane = NEGATIVE_Y;
        collide_y = true;
    }

    if(min_y <= other_box.max_y && max_y >= other_box.max_y)
    {
        plane = POSITIVE_Y;
        collide_y = true;
    }

    if(min_z <= other_box.min_z && max_z >= other_box.min_z)
    {
        plane = NEGATIVE_Z;
        collide_z = true;
    }

    if(min_z <= other_box.max_z && max_z >= other_box.max_z)
    {
        plane = POSITIVE_Z;
        collide_z = true;
    }

    return collide_x || collide_y || collide_z;
}