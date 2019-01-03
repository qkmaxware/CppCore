#include "System.Text.Csv.hpp"
#include <string>
#include <iterator>
#include <sstream>

namespace System {
namespace Text {


size_t Csv::Count() {
    return rows.size();
}

size_t Csv::Heading(const std::string& value) {
    size_t p = 0; 
    if(rows.size() < 1)
        return p;
    for(size_t t = 0; t < rows[0].size(); t++) {
        if(rows[0][t] == value)
            return t;
    }
    return p;
} 

std::vector<std::string>& Csv::operator [] (size_t t) {
    return rows[t];
}

Csv& Csv::operator << (std::vector<std::string>& row) {
    rows.push_back(row);
    return *this;
}

Csv& Csv::operator << (std::istream& str) {
    std::string line;
    while(std::getline(str, line)) {
        //Add a row
        rows.push_back(std::vector<std::string>());
        std::vector<std::string>& data = rows.back();
        //Parse cells
        std::stringstream lineStream(line);
        std::string cell;
        while(std::getline(lineStream,cell, ',')) {
            data.push_back(cell);
        }
        //Empty cell
        if (!lineStream && cell.empty()) {
            // If there was a trailing comma then add an empty element.
            data.push_back("");
        }
    }
    return *this;
}

}
}