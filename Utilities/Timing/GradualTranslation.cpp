#include "GradualTranslation.h"

GradualTranslation::GradualTranslation(float time, glm::vec3 end)
{
    translation_time = time;
    this->end = end;
    transition_complete = false;
}

void GradualTranslation::step_linear()
{
    //does a linear move step based on the difference in timestamps from before as long as we are still supposed to translate
    //if the translation is done, i.e. the total time is equal to the time that the translation was set to take, then we should set
    //that the translation is done and return
    timestep.record();
    total_time += timestep.getTimestep();

    if(total_time >= translation_time)
    {
        transition_complete = true;
        return;
    }

    object->move_to((float)(total_time/translation_time)*(end-start)+start);
}

void GradualTranslation::reset()
{
    total_time = 0;
    transition_complete = false;
}

void GradualTranslation::setObject(Object *o)
{
    object = o;
    start = glm::vec3(o->getMVP()->getModel()[3][0], o->getMVP()->getModel()[3][1], o->getMVP()->getModel()[3][2]);
}

void GradualTranslation::setEnd(glm::vec3 e)
{
    end = e;
    start = glm::vec3(object->getMVP()->getModel()[3][0], object->getMVP()->getModel()[3][1], object->getMVP()->getModel()[3][2]);
}

