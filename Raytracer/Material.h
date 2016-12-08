#pragma once
#include <memory>
#include <glm\glm.hpp>
#include "HitInfo.h"
#include "ScatteredRay.h"

class Material {
    glm::vec3 albedo;

public:
    Material(const glm::vec3& albedo) :
        albedo(albedo) {}

    virtual std::unique_ptr<ScatteredRay> getScattered(const Ray& in, const HitInfo* hit) const = 0;
    const glm::vec3& getAlbedo() const;
};
