#ifndef COMP_477_A1_TIMESTEP_H
#define COMP_477_A1_TIMESTEP_H

#include <GLFW/glfw3.h>
#include <iostream>

class Timestep
{
    private:
        double timestamp_a; //start of the timestep
        double timestamp_b; //end of the timestamp

    public:
        Timestep();
        void record();
        inline double getTimestep(){return timestamp_b - timestamp_a;}
        friend std::ostream& operator<<(std::ostream& os, Timestep& timestep);
};

#endif //COMP_477_A1_TIMESTEP_H
