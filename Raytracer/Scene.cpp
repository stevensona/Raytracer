#include "Scene.h"

#include <limits>

void Scene::addObject(std::unique_ptr<Object> object)
{
    objects.push_back(std::move(object));
}

std::unique_ptr<HitInfo> Scene::getHitInfo(const Ray & ray) const
{
    auto closest_hit = std::unique_ptr<HitInfo>(nullptr);
    float closest = std::numeric_limits<float>::max();

    for (auto& object : objects) {
        auto hit = object.get()->getHitInfo(ray, 0.001f, closest);
        if (hit != nullptr) {
            if (closest_hit == nullptr) {
                closest_hit = std::move(hit);
                closest = closest_hit->getDistance();
                continue;
            }
            if (hit->getDistance() < closest_hit->getDistance()) {
                closest_hit = std::move(hit);
                closest = closest_hit->getDistance();
            }
        }
    }
    return closest_hit;
}
