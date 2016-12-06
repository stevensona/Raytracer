#include "Ray.h"

glm::vec3 Ray::getOrigin() const
{
    return origin;
}

glm::vec3 Ray::getDirection() const
{
    return direction;
}

glm::vec3 Ray::getPoint(const float t) const
{
    return origin + direction * t;
}
