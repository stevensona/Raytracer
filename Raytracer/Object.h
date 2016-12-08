#pragma once

#include <memory>

#include "Material.h"
#include "HitInfo.h"
#include "Ray.h"

class Object {
    std::shared_ptr<Material> material;
public:
    void setMaterial(std::shared_ptr<Material> material);
    Material* getMaterial() const;

    virtual std::unique_ptr<HitInfo> getHitInfo(const Ray& ray, const float minDistance, const float maxDistance) const = 0;
};
