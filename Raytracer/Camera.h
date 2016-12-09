#pragma once

#include <glm\glm.hpp>
#include "Ray.h"

class Camera {

    glm::vec3 position;
    glm::vec3 center;
    glm::vec3 horizontal;
    glm::vec3 vertical;

public:
    Camera(const glm::vec3& position, const glm::vec3& target, const float fov, const float aspectRatio);

    Ray getRay(const float u, const float v) const;
};
