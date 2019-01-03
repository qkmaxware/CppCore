#include "System.Graphics.Image.hpp"

namespace System {
namespace Graphics {

Image::Image(uint width, uint height) : pixels(width * height), width(width), height(height) {}

Colour& Image::GetPixel(uint x, uint y) {
    return pixels[x + width * y];
}

uint Image::GetWidth() const {
    return width;
}

uint Image::GetHeight() const {
    return height;
}

}
}