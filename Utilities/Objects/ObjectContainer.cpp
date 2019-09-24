#include "ObjectContainer.h"

ObjectContainer::ObjectContainer() {size = 0;}

ObjectContainer::~ObjectContainer() {}

void ObjectContainer::addObject(Object* obj)
{
    objects.push_back(obj);
    size++;
}

