#pragma once

#include "Object.h"

class Sphere : public Object {
    glm::vec3 center;
    float radius;

public:
    Sphere(const glm::vec3& center, const float radius, std::shared_ptr<Material> material) :
        center(center),
        radius(radius) {
        setMaterial(material);
    }

    virtual std::unique_ptr<HitInfo> getHitInfo(const Ray& ray, const float minDistance, const float maxDistance) const override;
};