#pragma once

#include "Material.h"

class Metal : public Material {
    float roughness;

public:
    Metal(const glm::vec3 albedo, const float roughness = 0.0f) :
        Material(albedo) {
        setRoughness(roughness);
    }
    void setRoughness(const float roughness);
    float getRoughness() const;

    virtual std::unique_ptr<ScatteredRay> getScattered(const Ray& in, const HitInfo* hit) const override;

};
