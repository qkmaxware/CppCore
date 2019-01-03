#include "System.Graphics.Colour.hpp"

namespace System {
namespace Graphics {

Colour::Colour() : r(0), g(0), b(0), a(255) {}

Colour::Colour(uint r, uint g, uint b) : r(r % 256), g(g % 256), b(b % 256), a(255) {}

Colour::Colour(uint r, uint g, uint b, uint a) : r(r % 256), g(g % 256), b(b % 256), a(a % 256) {}

Colour::Colour(uint hex) : r((hex >> 16) & 0xFF), g((hex >> 8) & 0xFF), b(hex & 0xFF), a(255) {}

std::string Colour::ToHex(){
    std::stringstream sb;
    sb << "#";
    sb << std::hex;
    if(r <= 16){
        sb << '0';
    }
    sb << (r % 256);

    if(g <= 16){
        sb << '0';
    }
    sb << (g % 256);

    if(b <= 16){
        sb << '0';
    }
    sb << (b % 256);
    return sb.str();
}

float Colour::GetOpacity()  {
    return (a % 256) / 255.0;
}

Colour Colour::Darker(uint inc) {
    return Colour(this->r - inc, this->g - inc, this->b - inc, this->a);
}

Colour Colour::Lighter(uint inc) {
    return Colour(this->r + inc, this->g + inc, this->b + inc, this->a);
}

const Colour Colour::Red(0xFF0000); 

const Colour Colour::Green(0x00FF00); 

const Colour Colour::Blue(0x0000FF); 

const Colour Colour::White(0xFFFFFF);

const Colour Colour::Black(0x000000); 

const Colour Colour::Clear(0,0,0,0);

const Colour Colour::Teal(0,255,255);

const Colour Colour::Purple(255,0,255);

const Colour Colour::Yellow(255,255,0);

}
}