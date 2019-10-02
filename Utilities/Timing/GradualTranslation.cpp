#include "GradualTranslation.h"

GradualTranslation::GradualTranslation(float time, glm::vec3 start, glm::vec3 end)
{
    translation_time = time;
    this->start = start;
    this->end = end;
    transition_complete = false;
}

void GradualTranslation::step_linear()
{
    timestep.record();
    total_time += timestep.getTimestep();

    if(total_time > translation_time)
    {
        transition_complete = true;
        return;
    }

    object->move_to((float)(total_time/translation_time)*(end));
}

void GradualTranslation::reset()
{
    transition_complete = false;
    total_time = 0;
}

