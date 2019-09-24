#include "glm.hpp"
#include <iostream>

#ifndef COMP_371_A3_MVP
#define COMP_371_A3_MVP
//this class contains data for a model view projection matrix with perspective projection
class MVP
{
    private:
        glm::mat4 Model;
        glm::mat4 View;
        glm::mat4 Projection;
        glm::vec3 view_eye;
        glm::vec3 view_direction;
        glm::vec3 view_up;

    public:
        MVP();
        ~MVP();
        void setModel(glm::mat4);
        void setView(glm::vec3, glm::vec3, glm::vec3);
        void setView(glm::mat4);
        void setProjection(float, int, int, float, float); //must be called after window has been initialized
        inline glm::mat4 getModel(){return Model;}
        inline glm::mat4 getView(){return View;}
        inline glm::mat4 getProjection(){return Projection;}
        glm::mat4 getMVP();
        inline glm::vec3 getViewEye(){return view_eye;}
        inline glm::vec3 getViewDirection(){return view_direction;}
        inline glm::vec3 getViewUp(){return view_up;}
        void setViewEye(glm::vec3);
        void setViewDirection(glm::vec3);
        void setViewUp(glm::vec3);
};

#endif