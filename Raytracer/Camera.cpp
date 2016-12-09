#define _USE_MATH_DEFINES
#include <cmath>
#include <glm\gtc\random.hpp>
#include "Camera.h"

using namespace glm;

Camera::Camera(const vec3& position, const vec3& target, const float fov, const float aspectRatio, const float aperture, const float focalLength) :
    position(position) {

    auto theta = fov * (M_PI / 180.0);
    auto halfWidth = tan(theta / 2.0);
    auto halfHeight = aspectRatio / halfWidth;
   
    auto view = normalize(position - target);
    right = normalize(cross(vec3(0, 1.f, 0), view));
    up = cross(view, right);

    center = -1.f * view * focalLength;
    horizontal = 2.f * static_cast<float>(halfWidth) * right * focalLength;
    vertical = -2.f * static_cast<float>(halfHeight) * up * focalLength;

    lensRadius = aperture / 2.f;
}

Ray Camera::getRay(const float u, const float v) const
{
    auto rd = lensRadius * diskRand(1.f);
    auto offset = right * rd.x + up * rd.y;

    auto direction = center +
        horizontal * u - horizontal * 0.5f +
        vertical * v - vertical * 0.5f - offset;

    return Ray(position + offset, direction);
}
