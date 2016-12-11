#pragma once
#include <memory>
#include "Scene.h"
#include "Camera.h"

class Raytracer {
    Scene scene;
    Camera camera;

public:
    Raytracer(const Camera& camera) :
        scene(),
        camera(camera) {}

    Scene& getScene();

    glm::vec3 getColorFromRay(const Ray& ray, int depth = 0) const;

};
