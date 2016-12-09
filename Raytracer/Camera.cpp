#define _USE_MATH_DEFINES
#include <cmath>
#include "Camera.h"

using namespace glm;

Camera::Camera(const vec3& position, const vec3& target, const float fov, const float aspectRatio) :
    position(position) {

    auto theta = fov * (M_PI / 180.0);
    auto halfWidth = tan(theta / 2.0);
    auto halfHeight = aspectRatio / halfWidth;
   
    auto w = normalize(position - target);
    auto u = normalize(cross(vec3(0, 1.f, 0), w));
    auto v = cross(w, u);

    center = -1.f * w;
    horizontal = 2.f * static_cast<float>(halfWidth) * u;
    vertical = -2.f * static_cast<float>(halfHeight) * v;
}

Ray Camera::getRay(const float u, const float v) const
{
    using namespace glm;

    vec3 direction = center +
        horizontal * u - horizontal * 0.5f +
        vertical * v - vertical * 0.5f;

    return Ray(position, direction);
}
