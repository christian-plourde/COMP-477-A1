#ifndef UNIFORM_H
#define UNIFORM_H

#include <glew.h>

class Uniform
{
    private:
        GLint id;
        const char* uniform_name;
    public:
        Uniform(const char*);
        ~Uniform();
        inline GLint getID(){return id;}
        inline const char* getName(){return uniform_name;}
        inline void setID(GLint id_){id = id_;}
};

#endif