#include "Object.h"

void Object::setMaterial(std::shared_ptr<Material> material)
{
    this->material = material;
}

Material* Object::getMaterial() const
{
    return material.get();
}
