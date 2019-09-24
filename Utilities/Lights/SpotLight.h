#ifndef COMP_371_A3_SPOTLIGHT_H
#define COMP_371_A3_SPOTLIGHT_H

#include "glm.hpp"

class SpotLight
{
    private:
        glm::vec3 spot_position;
        glm::vec3 spot_direction;
        glm::vec3 spot_color;
        float cutoff_angle;
    public:
        SpotLight();
        ~SpotLight();
        inline void setPosition(glm::vec3 pos){spot_position = pos;}
        inline void setDirection(glm::vec3 dir){spot_direction = dir;}
        inline void setCutoffAngle(float angle){cutoff_angle = angle;}
        inline void setColor(glm::vec3 col){spot_color = col;}
        inline glm::vec3 getPosition(){return spot_position;}
        inline glm::vec3 getDirection(){return spot_direction;}
        inline glm::vec3 getColor(){return spot_color;}
        inline float getCutoffAngle(){return cutoff_angle;}
        void setPosition(float x, float y, float z);
        void setDirection(float x, float y, float z);
        void setColor(float x, float y, float z);
        float getCutoffCosine();

};

#endif
