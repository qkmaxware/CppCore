#include "System.Text.Parsing.hpp"

#include <sstream>

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

Parser<char> CharIn(const std::initializer_list<char> chars) {
    return  [=](const ParseIterator& it) -> ParseResult<char> {
        if(it.Length() != 0 && std::find(cbegin(chars), cend(chars), it.Peek()) != cend(chars)){
            return Success<char>(it.Peek(), it.Move(1));
        } else {
            return Failure<char>(it);
        }
    };
};

Parser<char> NotChar(char c) {
    return  [=](const ParseIterator& it) -> ParseResult<char> {
        if(it.Length() != 0 && it.Peek() != c){
            return Success<char>(it.Peek(), it.Move(1));
        } else {
            return Failure<char>(it);
        }
    };
};

Parser<char> ParseStringCharacter() {
    return  [=](const ParseIterator& it) -> ParseResult<char> {
        if(it.Length() == 0)
            return Failure<char>(it); //Missing char

        char c = it.Peek();
        if(c == '\\') {
            ParseIterator it2 = it.Move(1);
            if(it2.Length() == 0) 
                return Failure<char>(it); //Missing escaped char

            switch(it2.Peek()) {
                case '"':
                    case '\\':
                    case '/':
                        return Success<char>(it2.Peek(), it2.Move(1));
                    case 'b':
                        return Success<char>('\b', it2.Move(1));
                    case 'f':
                        return Success<char>('\f', it2.Move(1));
                    case 'n':
                        return Success<char>('\n', it2.Move(1));
                    case 'r': 
                        return Success<char>('\r', it2.Move(1));
                    case 't': 
                        return Success<char>('\t', it2.Move(1));
                    default:
                        return Failure<char>(it); //Not an escape character
            }            
        } else if(c == '"') {
            return Failure<char>(it); //Quote that has not been escaped
        } else {
            return Success<char>(c, it.Move(1)); //Was a literal
        }
    };
};

Parser<std::string> ExactString(const std::string& str) {
    return [=](const ParseIterator& it) -> ParseResult<std::string> {
        if(str.length() > it.Length())
            return Failure<std::string>(it);
        ParseIterator i = it;
        for(auto c : str) {
            if(i.Peek() == c) {
                i = i.Move(1);
            } else {
                return Failure<std::string>(it);
            }
        }
        return Success<std::string>(str, i);
    };
}

}
}
}
