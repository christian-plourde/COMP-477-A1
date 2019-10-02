#ifndef COMP_477_A1_PROBLEM_1_GRADUALTRANSLATION_H
#define COMP_477_A1_PROBLEM_1_GRADUALTRANSLATION_H

#include <glew.h>
#include <GLFW/glfw3.h>
#include "Timestep.h"
#include "../Objects/Object.h"
#include "../../GLM/glm/glm.hpp"

class GradualTranslation
{
    private:
        Object* object; //the object being translated
        float translation_time;
        float total_time;
        glm::vec3 start;
        glm::vec3 end;
        bool transition_complete;
        Timestep timestep;

    public:
        GradualTranslation(float time, glm::vec3 start, glm::vec3 end);
        void step_linear();
        void reset();
        inline void setStartEnd(glm::vec3 s, glm::vec3 e){start = s; end = e;}
        inline bool isComplete(){return transition_complete;}
        inline void setObject(Object* o){object = o;}
};

#endif //COMP_477_A1_PROBLEM_1_GRADUALTRANSLATION_H
