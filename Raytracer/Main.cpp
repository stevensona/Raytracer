#include <iostream>
#include <vector>
#include <random>
#include <future>

#include <glm\glm.hpp>
#include <glm\gtc\random.hpp>

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
        return (1.f - t) * vec3(1) + t * vec3(0.5f, 0.7f, 1.0f);
    }
    vec3 target = hit->getLocation() + hit->getNormal() + ballRand(1.f);
    Ray secondary(hit->getLocation(), target - hit->getLocation());
    return 0.5f * getColorFromRay(scene, secondary);
}

int main(int argc, char **argv) {
    using namespace std;
    using namespace glm;

    Image testImage(1027, 768, 4);
    
    const auto samples = 200;
    const auto threadCount = 8;

    Scene scene;
    scene.addObject(make_unique<Sphere>(Sphere(vec3(0, 0, -1), 0.5f)));
    scene.addObject(make_unique<Sphere>(Sphere(vec3(0, -100.5f, -1), 100)));

    Camera camera(vec3(0));

    default_random_engine gen;
    uniform_real_distribution<float> dist(0.f, 1.f);

    for (auto y = 0; y < testImage.getHeight(); ++y) {
        for (auto x = 0; x < testImage.getWidth(); ++x) {

            vector<future<vec3>> colorThreads;

            for (auto t = 0; t < threadCount; ++t) {
                colorThreads.push_back(async(launch::async, [&] {
                    vec3 color(0);
                    for (auto s = 0; s < samples / threadCount; ++s) {
                        auto horizontalFactor = (static_cast<float>(x) + dist(gen)) / static_cast<float>(testImage.getWidth());
                        auto verticalFactor = (static_cast<float>(y) + dist(gen)) / static_cast<float>(testImage.getHeight());
                        auto ray = camera.getRay(horizontalFactor, verticalFactor);
                        color += getColorFromRay(scene, ray);

                    }
                    return color;
                }));
            }

            vec3 color(0);
            for (auto colorPart = colorThreads.begin(); colorPart != colorThreads.end(); ++colorPart) {
                color += (*colorPart).get();
            }

            color /= static_cast<float>(samples);
            color = glm::sqrt(color);
            testImage.setPixel(x, y, Color32(color.r, color.g, color.b, 1.0f));

        }
    }
    testImage.save("output.png");
}
