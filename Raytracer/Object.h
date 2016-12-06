#pragma once

#include <memory>
#include "HitInfo.h"
#include "Ray.h"

class Object {

public:
    virtual std::unique_ptr<HitInfo> getHitInfo(const Ray& ray, const float minDistance, const float maxDistance) const = 0;
};
