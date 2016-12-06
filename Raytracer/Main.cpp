#include <iostream>
#include <vector>
#include <random>

#include <glm\glm.hpp>

#include "Image.h"
#include "Color32.h"
#include "Ray.h"
#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"

glm::vec3 getColorFromRay(const Scene& scene, const Ray& ray) {
    using namespace glm;

    auto hit = scene.getHitInfo(ray);
    
    if (hit == nullptr) {
        auto direction = normalize(ray.getDirection());
        auto t = 0.5f * (direction.y + 1.f);
        return (1.f - t) * vec3(0) + t * vec3(0.3f);
    }
    
    return 0.5f * (hit->getNormal() + vec3(1));
}

int main(int argc, char **argv) {
    using namespace std;
    using namespace glm;

    Image testImage(800, 600, 4);
    auto samples = 100;

    Scene scene;
    scene.addObject(make_unique<Sphere>(Sphere(vec3(0, 0, -1), 0.4f)));
    scene.addObject(make_unique<Sphere>(Sphere(vec3(0, -100.5f, -1), 100)));

    Camera camera(vec3(0));

    default_random_engine gen;
    uniform_real_distribution<float> dist(0.f, 1.f);

    for (auto y = 0; y < testImage.getHeight(); ++y) {
        for (auto x = 0; x < testImage.getWidth(); ++x) {
            vec3 color(0);

            for (auto s = 0; s < samples; ++s) {
                auto horizontalFactor = (static_cast<float>(x) + dist(gen)) / static_cast<float>(testImage.getWidth());
                auto verticalFactor = (static_cast<float>(y) + dist(gen)) / static_cast<float>(testImage.getHeight());

                auto ray = camera.getRay(horizontalFactor, verticalFactor);

                color += getColorFromRay(scene, ray);

            }
            color /= static_cast<float>(samples);

            testImage.setPixel(x, y, Color32(color.r, color.g, color.b, 1.0f));

        }
    }
    testImage.save("output.png");
}
