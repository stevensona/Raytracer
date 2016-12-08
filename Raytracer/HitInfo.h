#pragma once
#include <memory>
#include <glm\glm.hpp>

class Material;

class HitInfo {

    float distance;
    glm::vec3 location;
    glm::vec3 normal;
    Material* material;

public:
    HitInfo(const float distance, const glm::vec3& location, const glm::vec3& normal, Material* material) :
        distance(distance),
        location(location),
        normal(normal),
        material(material) {
    }
    
    float getDistance() const;
    glm::vec3 getLocation() const;
    glm::vec3 getNormal() const;
    Material* getMaterial() const;
    
};
