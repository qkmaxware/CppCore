#include "System.Graphics.PPMConverter.hpp"

namespace System {
namespace Graphics {
    
std::string PPMConverter::GetFileExtension() {
    return "ppm";
}

void PPMConverter::Convert(Image& image, std::ostream& stream) {
    //Header
    stream << "P3" << '\n';
    stream << image.GetWidth() << ' ' << image.GetHeight() << '\n';
    stream << "255\n";
    //Body
    for(uint row = 0; row < image.GetHeight(); row++) {
        for(uint column = 0; column < image.GetWidth(); column++){
            Colour& c = image.GetPixel(column, row);
            stream << c.r << ' ' << c.g << ' ' << c.b;
            if(column == image.GetWidth() - 1)
                stream << '\n';
            else 
                stream << ' ';
        }
    }
}

} // Graphics 
} // System
