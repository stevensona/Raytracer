#include <iostream>
#include <vector>

#include <glm\glm.hpp>

#include "Image.h"
#include "Color32.h"

int main(int argc, char **argv) {
    using namespace std;
    using namespace glm;

    Image testImage(800, 600, 4);

    for (auto y = 0; y < testImage.getHeight(); ++y) {
        for (auto x = 0; x < testImage.getWidth(); ++x) {

            vec3 color(
                static_cast<float>(x) / static_cast<float>(testImage.getWidth()),
                static_cast<float>(testImage.getHeight() - y) / static_cast<float>(testImage.getHeight()),
                0.2f);

            testImage.setPixel(x, y, Color32(color.r, color.g, color.b, 1.0f));

        }
    }
    testImage.save("output.png");
}
