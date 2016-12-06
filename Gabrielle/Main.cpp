#include <iostream>
#include <vector>

#include <glm\glm.hpp>

#include "Image.h"
#include "Color32.h"
#include "Ray.h"

float doesHitSphere(const glm::vec3& center, float radius, const Ray& ray) {
    using namespace glm;
    auto oc = ray.getOrigin() - center;
    auto a = dot(ray.getDirection(), ray.getDirection());
    auto b = 2.f * dot(oc, ray.getDirection());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return -1.f;
    }
    else {
        return (-b - sqrt(discriminant)) / (2.f * a);
    }
}

glm::vec3 getColorFromRay(const Ray& ray) {
    using namespace glm;

    vec3 spherePos(0, 0, -1);
    auto t = doesHitSphere(spherePos, 0.5, ray);
    if(t > 0) {
        vec3 normal = normalize(ray.getPoint(t) - spherePos);
        return 0.5f * (normal + vec3(1));
    }
    //return a gradient from blue to white
    auto direction = normalize(ray.getDirection());
    t = 0.5f * (direction.y + 1.f);
    return (1.f - t) * vec3(1) + t * vec3(0.5f, 0.7f, 1.f);
}

int main(int argc, char **argv) {
    using namespace std;
    using namespace glm;

    Image testImage(800, 600, 4);

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

            auto color = getColorFromRay(ray);

            testImage.setPixel(x, y, Color32(color.r, color.g, color.b, 1.0f));

        }
    }
    testImage.save("output.png");
}
