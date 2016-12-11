#include "Raytracer.h"

using namespace glm;

Scene& Raytracer::getScene()
{
    return scene;
}

vec3 Raytracer::getColorFromRay(const Ray & ray, int depth) const
{
    auto hit = scene.getHitInfo(ray);

    if (hit == nullptr) {
        auto direction = normalize(ray.getDirection());
        auto t = 0.5f * (direction.y + 1.f);
        return (1.f - t) * vec3(1) + t * vec3(0.3f, 0.6f, 0.9f);
    }

    auto secondary = hit->getMaterial()->getScattered(ray, hit.get());
    if (depth > 50 || secondary == nullptr) {
        return vec3(0.f);
    }

    return secondary->getAttenuation() * getColorFromRay(*secondary.get(), depth + 1);
}
