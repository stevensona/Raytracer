#pragma once
#include "Material.h"


class Lambert : public Material {

public:
    Lambert(const glm::vec3 albedo) :
        Material(albedo) {}

    virtual std::unique_ptr<ScatteredRay> getScattered(const Ray& in, const HitInfo* hit) const override;

};
