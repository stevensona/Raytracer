#pragma once

#include <glm\glm.hpp>
#include "Ray.h"

class Camera {

    glm::vec3 position;
    glm::vec3 center;
    glm::vec3 horizontal;
    glm::vec3 vertical;

public:
    //TODO fov, "look-at" function
    Camera(const glm::vec3& position);

    Ray getRay(const float u, const float v) const;
};
