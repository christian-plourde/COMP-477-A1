#ifndef COMP_477_A1_BOUNDINGBOX_H
#define COMP_477_A1_BOUNDINGBOX_H
#include <glew.h>
#include <vector>
#include "../../GLM/glm/glm.hpp"
#include "../../GLM/glm/matrix.hpp"
#include "../../GLM/glm/gtc/matrix_transform.hpp"
#include "../ErrorHandling/ErrorHandlingFunctions.h"
#include "MVP.h"
#include "../Shading/Shader.h"

enum CollisionPlane {POSITIVE_X, NEGATIVE_X, POSITIVE_Y, NEGATIVE_Y, POSITIVE_Z, NEGATIVE_Z};

class BoundingBox
{
    private:
        float max_x;
        float max_y;
        float max_z;
        float min_x;
        float min_y;
        float min_z;
        float scale_factor;
        MVP* mvp;
        std::vector<glm::vec3> vertices;

    public:
        BoundingBox();
        ~BoundingBox();
        void setVertices(std::vector<glm::vec3>* vertices);
        inline void setMVP(MVP* mvp){this->mvp = mvp;}
        inline MVP* getMVP(){return mvp;}
        friend std::ostream& operator<<(std::ostream& os, BoundingBox& box);
        bool collides_with(BoundingBox& other_box, CollisionPlane& plane);
        inline void setScaleFactor(float factor){scale_factor = factor;}
};

#endif //COMP_477_A1_BOUNDINGBOX_H
