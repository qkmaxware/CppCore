#include "System.Graphics.TARGAConverter.hpp"

namespace System {
namespace Graphics {

std::string TARGAConverter::GetFileExtension() {
    return "tga";
}

void TARGAConverter::Convert(Image& image, std::ostream& stream) {
    //Header
    char header[18];
    header[0] = 0; //ID Length
    header[1] = 0; //Colour map type (no colour map)
    header[2] = 2; //Image type (uncompressed true-colour image)
    //Width (2 bytes)
    header[12] = 255 & image.GetWidth();
    header[13] = 255 & (image.GetWidth() >> 8);
    //Height (2 bytes)
    header[14] = 255 & image.GetHeight();
    header[15] = 255 & (image.GetHeight() >> 8);
    header[16] = 24; //Pixel depth
    header[17] = 32; //
    stream.write(header, 18);

    //Body
    for(uint row = 0; row < image.GetHeight(); row++) {
        for(uint column = 0; column < image.GetWidth(); column++){
            Colour& c = image.GetPixel(column, row);
            stream.put(static_cast<char>(c.r));
            stream.put(static_cast<char>(c.g));
            stream.put(static_cast<char>(c.b));
        }
    }
}

} // Graphics 
} // System
