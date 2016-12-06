#include <exception>
#include <lodepng.h>

#include "Image.h"

void Image::save(const std::string & filename)
{
    lodepng::encode(filename, buffer, width, height);
}

void Image::setPixel(const unsigned x, const unsigned y, const Color32& color)
{
    auto base = y * bpp * width + x * bpp;
    buffer[base + Red] = color.red;
    buffer[base + Green] = color.green;
    buffer[base + Blue] = color.blue;
    buffer[base + Alpha] = color.alpha;
}

Color32 Image::getPixel(const unsigned x, const unsigned y) const
{
    auto base = y * bpp * width + x * bpp;
    return Color32(
        buffer[base + Red],
        buffer[base + Green],
        buffer[base + Blue],
        buffer[base + Alpha]);
}

unsigned Image::getWidth() const
{
    return width;
}

unsigned Image::getHeight() const
{
    return height;
}

unsigned Image::getBpp() const
{
    return bpp;
}
