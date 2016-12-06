#pragma once

#include <vector>
#include <memory>
#include "Object.h"

class Scene {
    
    std::vector<std::unique_ptr<Object>> objects;

public:
    Scene() : objects() {}

    void addObject(std::unique_ptr<Object> object);

    std::unique_ptr<HitInfo> getHitInfo(const Ray& ray) const;


};