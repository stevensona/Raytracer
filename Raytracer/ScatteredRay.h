#pragma once

#include "Ray.h"

class ScatteredRay : public Ray {
    glm::vec3 attenuation;

public:
    ScatteredRay(const glm::vec3& origin, const glm::vec3& direction, const glm::vec3& attenuation) :
        Ray(origin, direction),
        attenuation(attenuation) {}

    glm::vec3 getAttenuation() const;

};
