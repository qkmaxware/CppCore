#ifndef _SYSTEM_TEXT_CSV_HPP
#define _SYSTEM_TEXT_CSV_HPP

#include <vector>
#include <iostream>

namespace System {
namespace Text {

class Csv {
    private:
        std::vector<std::vector<std::string>> rows;

    public:
        size_t Count();

        size_t Heading(const std::string& value);

        std::vector<std::string>& operator [] (size_t t);

        Csv& operator << (std::vector<std::string>& row);

        Csv& operator << (std::istream& str);
};

}
}

#endif