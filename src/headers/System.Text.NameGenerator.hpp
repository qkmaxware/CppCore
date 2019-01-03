#ifndef _SYSTEM_TEXT_NAMEGENERATOR_HPP
#define _SYSTEM_TEXT_NAMEGENERATOR_HPP

#include <random>
#include <initializer_list>
#include <vector>

namespace System {
namespace Text {
 
class NameGenerator {
    private:
        std::vector<std::string> names;
        std::vector<std::string> desc;
        std::default_random_engine generator;
                    
    public:
        NameGenerator();
        
        NameGenerator(const std::initializer_list<std::string>& descriptors, const std::initializer_list<std::string>& names);

        std::string Next();
};

}
}

#endif