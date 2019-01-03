#ifndef _SYSTEM_GRAPHICS_IMAGECONVERTER_HPP
#define _SYSTEM_GRAPHICS_IMAGECONVERTER_HPP

#include "System.Graphics.Image.hpp"
#include <iostream>

namespace System {
namespace Graphics {

class IImageConverter {
    public: 
        virtual std::string GetFileExtension() = 0;
        virtual void Convert(Image& image, std::ostream& stream) = 0;
};

}
}

#endif