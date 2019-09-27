#ifndef COMP_477_A1_BOUNDINGBOX_H
#define COMP_477_A1_BOUNDINGBOX_H
#include <glew.h>
#include <vector>
#include "../../GLM/glm/glm.hpp"
#include "../ErrorHandling/ErrorHandlingFunctions.h"
#include "MVP.h"
#include "../Shading/Shader.h"

class BoundingBox
{
    private:
        float max_x;
        float max_y;
        float max_z;
        float min_x;
        float min_y;
        float min_z;
        MVP* mvp;
        std::vector<glm::vec3> vertices;

    public:
        BoundingBox();
        ~BoundingBox();
        void setVertices(std::vector<glm::vec3>* vertices);
        inline void setMVP(MVP* mvp){this->mvp = mvp;}
        inline MVP* getMVP(){return mvp;}
        friend std::ostream& operator<<(std::ostream& os, BoundingBox& box);
};

#endif //COMP_477_A1_BOUNDINGBOX_H
