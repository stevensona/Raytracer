#pragma once

#include <glm\glm.hpp>

class Ray {
    glm::vec3 origin;
    glm::vec3 direction;


public:
    Ray(const glm::vec3& origin, const glm::vec3& direction) :
        origin(origin),
        direction(direction) {}

    glm::vec3 getOrigin() const;
    glm::vec3 getDirection() const;
    glm::vec3 getPoint(const float t) const;

};
