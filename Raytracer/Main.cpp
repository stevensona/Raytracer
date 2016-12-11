#include <iostream>
#include <vector>
#include <random>
#include <future>

#include <glm\glm.hpp>

#include "Raytracer.h"
#include "Image.h"
#include "Color32.h"
#include "Ray.h"
#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"
#include "Lambert.h"
#include "Metal.h"


int main(int argc, char **argv) {
    using namespace std;
    using namespace glm;

    Image testImage(800, 600, 4);
    
    const auto totalSamples = 128;
    const auto threadCount = 8;

    default_random_engine gen;


    shared_ptr<Material> matGround = make_shared<Lambert>(vec3(0.15f, 0.15f, 0.15f));
    
    shared_ptr<Material> materials[5];

    materials[0] = make_shared<Lambert>(vec3(0.8f, 0.3f, 0.3f));
    materials[1] = make_shared<Lambert>(vec3(0.3f, 0.3f, 0.8f));
    materials[2] = make_shared<Lambert>(vec3(0.3f, 0.8f, 0.3f));
    
    materials[3] = make_shared<Metal>(vec3(0.8f, 0.6f, 0.2f), 0.05f);
    materials[4] = make_shared<Metal>(vec3(0.8f,0.8f,0.8f), 0.01f);
    
    auto ratio = static_cast<float>(testImage.getWidth()) / static_cast<float>(testImage.getHeight());

    vec3 camPos(7.f, 5.f, -7.f);
    vec3 camTarget(0.f);
    Camera camera(camPos, camTarget, 110.f, ratio, 0.05f, static_cast<float>((camTarget - camPos).length()));

    Raytracer tracer(camera);

    uniform_real_distribution<float> sizeDist(0.6f, 2.5f);
    uniform_real_distribution<float> posDist(-15.f, 15.f);
    uniform_int_distribution<> matDist;

    for (auto i = 0; i < 50; ++i) {
        auto size = sizeDist(gen);
        auto mat = matDist(gen) % 5;

        auto x = posDist(gen);
        auto z = posDist(gen);
        tracer.getScene().addObject(make_unique<Sphere>(Sphere(vec3(x, size, z), size, materials[mat])));

    }
    //tracer.getScene().addObject(make_unique<Sphere>(Sphere(vec3(0, 0, 0), 0.5f, matRed)));
    //tracer.getScene().addObject(make_unique<Sphere>(Sphere(vec3(1.3f, 0, 0), 0.5f, matGold)));
    
    
    tracer.getScene().addObject(make_unique<Sphere>(Sphere(vec3(0, -1000.f, 0), 1000, matGround)));


    uniform_real_distribution<float> dist(0.f, 1.f);

    for (auto y = 0; y < testImage.getHeight(); ++y) {
        for (auto x = 0; x < testImage.getWidth(); ++x) {

            vector<future<vec3>> colorThreads;

            for (auto t = 0; t < threadCount; ++t) {
                colorThreads.push_back(async(launch::async, [&] {
                    vec3 color(0);
                    for (auto s = 0; s < totalSamples / threadCount; ++s) {
                        auto horizontalFactor = (static_cast<float>(x) + dist(gen)) / static_cast<float>(testImage.getWidth());
                        auto verticalFactor = (static_cast<float>(y) + dist(gen)) / static_cast<float>(testImage.getHeight());
                        auto ray = camera.getRay(horizontalFactor, verticalFactor);
                        color += tracer.getColorFromRay(ray);

                    }
                    return color;
                }));
            }

            vec3 color(0);
            for (auto& colorPart : colorThreads) {
                color += colorPart.get();
            }

            color /= static_cast<float>(totalSamples);
            color = glm::sqrt(color);
            testImage.setPixel(x, y, Color32(color.r, color.g, color.b, 1.0f));

        }
    }
    testImage.save("output.png");
}
