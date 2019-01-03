#ifndef _SYSTEM_GRAPHICS_PPMCONVERTER_HPP
#define _SYSTEM_GRAPHICS_PPMCONVERTER_HPP

#include "System.Graphics.ImageConverter.hpp"

namespace System {
namespace Graphics {

class PPMConverter : public IImageConverter, public System::Object {
    public: 
        std::string GetFileExtension();
        void Convert(Image& image, std::ostream& stream);
};

}
}

#endif