#include "Sphere.h"

std::unique_ptr<HitInfo> Sphere::getHitInfo(const Ray& ray, const float minDistance, const float maxDistance) const
{
    using namespace glm;
    auto oc = ray.getOrigin() - center;
    auto a = dot(ray.getDirection(), ray.getDirection());
    auto b = 2.f * dot(oc, ray.getDirection());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        auto sqrtDiscriminant = sqrt(discriminant);
        auto twoA = 2.f * a;

        auto solution = (-b - sqrtDiscriminant) / twoA;

        if (solution > minDistance && solution < maxDistance) {
            auto location = ray.getPoint(solution);
            return std::make_unique<HitInfo>(HitInfo(solution, location, normalize(location - center)));
        }

        solution = (-b - sqrtDiscriminant) / twoA;
        if (solution > minDistance && solution < maxDistance) {
            auto location = ray.getPoint(solution);
            return std::make_unique<HitInfo>(HitInfo(solution, location, normalize(location - center)));
        }
    }

    return std::unique_ptr<HitInfo>(nullptr);
}
