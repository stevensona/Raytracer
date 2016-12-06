#pragma once

#include <string>
#include <vector>
#include "Color32.h"

class Image {
    unsigned width, height, bpp;
    std::vector<uchar8> buffer;

    enum ComponentOffset { Red, Green, Blue, Alpha };

public:
    Image(const unsigned width, const unsigned height, const unsigned bpp) :
        width(width),
        height(height),
        bpp(bpp),
        buffer(width * height * bpp) {}

    void save(const std::string& filename);
    void setPixel(const unsigned x, const unsigned y, const Color32& color);
    Color32 getPixel(const unsigned x, const unsigned y) const;
    unsigned getWidth() const;
    unsigned getHeight() const;
    unsigned getBpp() const;



};
