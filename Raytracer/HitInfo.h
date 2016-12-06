#pragma once

#include <glm\glm.hpp>

class HitInfo {

    float distance;
    glm::vec3 location;
    glm::vec3 normal;

public:
    HitInfo(const float distance, const glm::vec3& location, const glm::vec3& normal) :
        distance(distance),
        location(location),
        normal(normal) {}
    
    float getDistance() const;
    glm::vec3 getLocation() const;
    glm::vec3 getNormal() const;
    
};
