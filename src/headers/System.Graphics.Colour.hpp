#ifndef _SYSTEM_GRAPHICS_COLOUR_HPP
#define _SYSTEM_GRAPHICS_COLOUR_HPP

#include "System.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>

namespace System {
namespace Graphics {

/// <Summary>
/// Colour represented in red, green, blue, alpha with values from 0 to 255.
/// </Summary>
struct Colour {
    /// <Summary>
    /// Red
    /// </Summary>
    uint r;
    /// <Summary>
    ///Green
    /// </Summary>
    uint g;
    /// <Summary>
    /// Blue
    /// </Summary>
    uint b;
    /// <Summary>
    ///Alpha
    /// </Summary>
    uint a;

    /// <Summary>
    /// Solid Black
    /// </Summary>
    Colour();
    /// <Summary>
    /// Create a solid Colour
    /// </Summary>
    Colour(uint r, uint g, uint b);
    /// <Summary>
    /// Create a transparent Colour
    /// </Summary>
    Colour(uint r, uint g, uint b, uint a);
    /**
     * Create a color from the given hex code 
     */
    Colour(uint hex);

    /// <Summary>
    /// Create string in the form #RRGGBB
    /// </Summary>
    std::string ToHex();

    /// <Summary>
    /// Get opacity as a float in the range 0 to 1
    /// </Summary>
    float GetOpacity();

    /**
     * Get a colour that is darker than this one 
     */
    Colour Darker(uint increment = 4);

    /**
     * Get a colour that is lighter than this one 
     */
    Colour Lighter(uint increment = 4);

    /// <Summary>
    /// Solid red
    /// </Summary>
    static const Colour Red;
    /// <Summary>
    /// Solid green
    /// </Summary>
    static const Colour Green;
    /// <Summary>
    /// Solid blue
    /// </Summary>
    static const Colour Blue;
    /// <Summary>
    /// Solid white
    /// </Summary>
    static const Colour White;
    /// <Summary>
    /// Solid black
    /// </Summary>
    static const Colour Black;
    /// <Summary>
    /// Fully transparent Colour
    /// </Summary>
    static const Colour Clear;
    /// <Summary>
    /// Solid teal
    /// </Summary>
    static const Colour Teal;
    /// <Summary>
    /// Solid purple
    /// </Summary>
    static const Colour Purple;
    /// <Summary>
    /// Solid yellow
    /// </Summary>
    static const Colour Yellow;
};

}
}

#endif