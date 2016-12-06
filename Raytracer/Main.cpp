#include <iostream>
#include <vector>

#include <glm\glm.hpp>

#include "Image.h"
#include "Color32.h"
#include "Ray.h"
#include "Scene.h"
#include "Sphere.h"

glm::vec3 getColorFromRay(const Scene& scene, const Ray& ray) {
    using namespace glm;

    auto hit = scene.getHitInfo(ray);
    
    if(hit != nullptr) {
        return 0.5f * (hit->getNormal() + vec3(1));
    }
    //return a gradient from blue to white
    auto direction = normalize(ray.getDirection());
    auto t = 0.5f * (direction.y + 1.f);
    return (1.f - t) * vec3(1) + t * vec3(0.5f, 0.7f, 1.f);
}

int main(int argc, char **argv) {
    using namespace std;
    using namespace glm;

    Image testImage(800, 600, 4);

    Scene scene;
    scene.addObject(make_unique<Sphere>(Sphere(vec3(0, 0, -1), 0.4f)));
    scene.addObject(make_unique<Sphere>(Sphere(vec3(0, -100.5f, -1), 100)));

    vec3 origin(0);
    vec3 target(0, 0, -1.f);

    vec3 horizontal(4.f, 0, 0);
    vec3 vertical(0, -3.f, 0);

    for (auto y = 0; y < testImage.getHeight(); ++y) {
        for (auto x = 0; x < testImage.getWidth(); ++x) {

            auto horizontalFactor = static_cast<float>(x) / static_cast<float>(testImage.getWidth());
            auto verticalFactor = static_cast<float>(y) / static_cast<float>(testImage.getHeight());

            vec3 direction = target +
                horizontal * horizontalFactor - horizontal * 0.5f +
                vertical * verticalFactor - vertical * 0.5f;

            Ray ray(origin, direction);

            auto color = getColorFromRay(scene, ray);

            testImage.setPixel(x, y, Color32(color.r, color.g, color.b, 1.0f));

        }
    }
    testImage.save("output.png");
}
