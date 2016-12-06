#include "HitInfo.h"

glm::vec3 HitInfo::getNormal() const
{
    return normal;
}

float HitInfo::getDistance() const
{
    return distance;
}

glm::vec3 HitInfo::getLocation() const
{
    return location;
}
