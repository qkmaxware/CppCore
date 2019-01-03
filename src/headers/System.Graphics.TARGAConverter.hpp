#ifndef _SYSTEM_GRAPHICS_TARGACONVERTER_HPP
#define _SYSTEM_GRAPHICS_TARGACONVERTER_HPP

#include "System.Graphics.ImageConverter.hpp"

namespace System {
namespace Graphics {

class TARGAConverter : public IImageConverter, public System::Object {
    public: 
        std::string GetFileExtension();
        void Convert(Image& image, std::ostream& stream);
};

}
}

#endif