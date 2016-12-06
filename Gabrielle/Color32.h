#pragma once

using uchar8 = unsigned char;

class Color32 {
public:
    uchar8 red, green, blue, alpha;
    Color32(const uchar8 red, const uchar8 green, const uchar8 blue, const uchar8 alpha) :
        red(red),
        green(green), 
        blue(blue),
        alpha(alpha) {}

    Color32(const float red, const float green, const float blue, const float alpha) :
        red(static_cast<uchar8>(red * 255.99f)),
        green(static_cast<uchar8>(green * 255.99f)),
        blue(static_cast<uchar8>(blue * 255.99f)),
        alpha(static_cast<uchar8>(alpha * 255.99f)) {}

};