#include <iostream>
#include <vector>
#include <glm\glm.hpp>
#include <lodepng.h>

int main(int argc, char **argv) {
    using namespace std;
    using namespace glm;

    cout << "checking dependencies...\n";

    vec3 vec{ 1, 2, 3 };
    cout << "instantiated vector= {" << vec.x << ',' << vec.y << ',' << vec.z << "}\n";

    auto width = 512, height = 512;
    auto bytesperpixel = 4;
    enum ComponentOffset {
        Red,
        Green,
        Blue,
        Alpha
    };

    vector<unsigned char> image(bytesperpixel * width * height);
    for (auto y = 0; y < height; ++y) {
        for (auto x = 0; x < width; ++x) {
            auto pixel_start = y * bytesperpixel * width + x * bytesperpixel;
            float r = static_cast<float>(x) / static_cast<float>(width);
            float g = static_cast<float>(height - y) / static_cast<float>(height);

            image[pixel_start + Red] = static_cast<unsigned char>(r * 255.99f);
            image[pixel_start + Green] = static_cast<unsigned char>(g * 255.99f);
            image[pixel_start + Blue] = static_cast<unsigned char>(0.2f * 255.99f);
            image[pixel_start + Alpha] = 255;
        }
    }

    lodepng::encode("output.png", image, width, height);

}
