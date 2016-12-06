#include "Camera.h"

Camera::Camera(const glm::vec3 & position) : position(position) {
    center = position + glm::vec3(0, 0, -1);
    horizontal = glm::vec3(4.f, 0, 0);
    vertical = glm::vec3(0, -3.f, 0);
}

Ray Camera::getRay(const float u, const float v) const
{
    using namespace glm;

    vec3 direction = center +
        horizontal * u - horizontal * 0.5f +
        vertical * v - vertical * 0.5f;

    return Ray(position, direction);
}
