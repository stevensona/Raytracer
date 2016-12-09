#pragma once

#include <glm\glm.hpp>
#include "Ray.h"

class Camera {

    glm::vec3 position;
    glm::vec3 center;
    glm::vec3 horizontal;
    glm::vec3 vertical;

    glm::vec3 up;
    glm::vec3 right;

    float lensRadius;

public:
    Camera(const glm::vec3& position, const glm::vec3& target, const float fov, const float aspectRatio, const float aperture, const float focalLength);

    Ray getRay(const float u, const float v) const;
};
