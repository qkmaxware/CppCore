#ifndef _SYSTEM_GRAPHICS_IMAGE_HPP
#define _SYSTEM_GRAPHICS_IMAGE_HPP

#include "System.Graphics.Colour.hpp"
#include <vector>

namespace System {
namespace Graphics {

class Image : public System::Object {
    private:
        std::vector<Colour> pixels;
        uint width;
        uint height;

    public:
        Image(uint width, uint height);

        Colour& GetPixel(uint x, uint y);
        uint GetWidth() const;
        uint GetHeight() const;
};

}
}

#endif