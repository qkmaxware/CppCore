#include "System.Text.Parsing.hpp"

namespace System {
namespace Text {
namespace Parsing {


ParseIterator::ParseIterator(const std::string& data): begin(data.cbegin()), end(data.cend()) {}
ParseIterator::ParseIterator(const std::string::iterator& b, const std::string::iterator& e): begin(b), end(e) {}
ParseIterator::ParseIterator(const std::string::const_iterator& b, const std::string::const_iterator& e): begin(b), end(e) {}
ParseIterator::ParseIterator(const ParseIterator& other) = default;
std::string::size_type ParseIterator::Length() const {
    return end - begin;
}
char ParseIterator::Peek() const {
    return *begin;
}
bool ParseIterator::Eoit() const {
    return begin == end;
}
ParseIterator ParseIterator::Move(std::string::size_type distance) const {
    if(distance > Length()) {
        return ParseIterator(this->end, this->end); //Eoit
    }
    return ParseIterator(this->begin + distance, this->end);
}
ParseIterator ParseIterator::Slice(std::string::size_type start, std::string::size_type stop) const {
    if(stop < start) {
        return ParseIterator(this->begin, this->begin); //Don't move
    }
    if(stop > Length()) {
        return ParseIterator(this->end, this->end); //Eoit
    }
    return ParseIterator(begin + start, begin + stop);
}

Parser<bool> Always() {
    return [](const ParseIterator& it) -> ParseResult<bool> {
        return Success<bool>(true, it);
    };
}

Parser<bool> Never() {
    return [](const ParseIterator& it) -> ParseResult<bool> {
        return Failure<bool>(it);
    };
}

Parser<bool> End() {
    return [](const ParseIterator& it) -> ParseResult<bool> {
        if(it.Eoit()) {
            return Success<bool>(true, it);
        } else {
            return Failure<bool>(it);
        }
    };
}

Parser<char> Char(char c) {
    return [=](const ParseIterator& it) -> ParseResult<char> {
        if(it.Length() != 0 && it.Peek() == c){
            return Success<char>(c, it.Move(1));
        } else {
            return Failure<char>(it);
        }
    };
}

Parser<char> Range(char start, char end) {
    return [=](const ParseIterator& it) -> ParseResult<char> {
        if(it.Length() != 0 && it.Peek() >= start && it.Peek() <= end){
            return Success<char>(it.Peek(), it.Move(1));
        } else {
            return Failure<char>(it);
        }
    };
}

}
}
}