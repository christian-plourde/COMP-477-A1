#ifndef DEPTH_MAP_LIGHT_H
#define DEPTH_MAP_LIGHT_H

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

class DepthMapLight
{
    private:
        float near_plane;
        float far_plane;
        float fov;
        glm::vec3 eye;
        glm::vec3 looking_at;
        glm::vec3 up_vector;
        glm::mat4 projection;
        glm::mat4 view;
        glm::mat4 light_matrix;
        glm::mat4 model;
        void CalcLightMatrix();

    public:
        DepthMapLight();
        ~DepthMapLight();
        inline glm::mat4 getLightMatrix(){return light_matrix;}
        inline void setNearPlane(float v){near_plane = v; CalcLightMatrix();}
        inline void setFarPlane(float v){far_plane = v; CalcLightMatrix();}
        inline void setEye(glm::vec3 e){eye = e; CalcLightMatrix();}
        inline void setLookingAt(glm::vec3 v){looking_at = v; CalcLightMatrix();}
        inline void setUpVector(glm::vec3 v){up_vector = v; CalcLightMatrix();}
        void setProjection(float, int, int, float, float);
        inline glm::vec3 getEye(){return eye;}
        inline glm::mat4 getModel(){return model;}
        inline glm::mat4 getView(){return view;}
        inline glm::mat4 getProjection(){return projection;}

};

#endif