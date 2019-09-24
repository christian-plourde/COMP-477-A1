#ifndef OBJECT_CONTAINER_H
#define OBJECT_CONTAINER_H

#include "Object.h"

class ObjectContainer
{
    private:
        std::vector<Object*> objects;

    public:
        ObjectContainer();
        ~ObjectContainer();
        void addObject(Object* obj);
        inline std::vector<Object*> getObjects(){return objects;}
        inline Object* getObject(int i){return objects[i];}
        int size;
};

#endif