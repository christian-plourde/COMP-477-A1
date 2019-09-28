#include "Timestep.h"

Timestep::Timestep()
{
    timestamp_a = 0;
    timestamp_b = 0;
}

void Timestep::record()
{
    double old_time_b = timestamp_b;
    timestamp_b = glfwGetTime();
    timestamp_a = old_time_b;
}

std::ostream& operator<<(std::ostream& os, Timestep& timestep)
{
    os << timestep.getTimestep();
    return os;
}