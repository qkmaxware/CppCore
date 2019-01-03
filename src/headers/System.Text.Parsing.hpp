#ifndef _SYSTEM_TEXT_PARSING
#define _SYSTEM_TEXT_PARSING

#include <iostream>
#include <functional>
#include <utility>
#include <vector>
#include <regex>
#include <variant>
#include <limits>

namespace System {
namespace Text {
namespace Parsing {

struct ParseIterator {
    public:
        const std::string::const_iterator begin;
        const std::string::const_iterator end;

        ParseIterator(const std::string& data);
        ParseIterator(const std::string::iterator& b, const std::string::iterator& e);
        ParseIterator(const std::string::const_iterator& b, const std::string::const_iterator& e);
        ParseIterator(const ParseIterator& other);

        std::string::size_type Length() const;

        char Peek() const;

        bool Eoit() const;

        ParseIterator Move(std::string::size_type distance) const;

        ParseIterator Slice(std::string::size_type start, std::string::size_type stop) const;
};

template <typename T>
struct ParseResult {
    const bool success;
    const T value;
    const ParseIterator remaining;

    ParseResult() : success(false), value(), remaining() {}
    ParseResult(bool yes, const T& value, const ParseIterator& it): success(yes), value(value), remaining(it) {}
    ParseResult(const ParseResult<T>& other): success(other.success), value(other.value), remaining(other.remaining) {}
    ~ParseResult() = default;

    operator bool() {
        return success;
    }
};

template <typename T>
ParseResult<T> Success(const T& value, const ParseIterator& remaining) {
    return ParseResult<T>(
        true,
        value,
        remaining
    );
}

template <typename T>
ParseResult<T> Failure(const ParseIterator& remaining) {
    return ParseResult<T>(
        false,
        T(),
        remaining
    );
}

template <typename T>
using Parser = std::function<ParseResult<T>(const ParseIterator&)>;

//Base Parsers
Parser<bool> Always();

Parser<bool> Never();

Parser<bool> End();

Parser<char> Char(char c);

Parser<char> Range(char start, char end);


const Parser<char> Digit = Range('0', '9');

const Parser<char> Lowercase = Range('a', 'z');

const Parser<char> Uppercase = Range('A', 'Z');

const Parser<char> Alpha = Range('a', 'Z');

const Parser<char> AlphaNumeric = Range('0', 'Z'); //Maybe replace with Or(Digit, Alpha)

//Combinators
//Return the results of all parsers in sequence, fails if any fail
template <typename T, typename K>
Parser<std::tuple<T,K>> Sequence(const Parser<T>& first, const Parser<K>& next) {
    return [=](const ParseIterator& it) -> ParseResult<std::tuple<T,K>> { 
        ParseResult<T> r1 = first(it);
        if(!r1)
            return Failure<std::tuple<T,K>>(it);
        ParseResult<K> r2 = next(r1.remaining);
        if(!r2)
            return Failure<std::tuple<T,K>>(it);
        return Success(std::make_tuple(r1.value, r2.value), r2.remaining);
    };
}
template <typename T, typename ... Ks>
Parser<std::tuple<T,Ks ...>> Sequence(const Parser<T>& first, const Parser<Ks>& ... next) {
    Parser<std::tuple<Ks ...>> p2 = Sequence(next ...);
    return [=](const ParseIterator& it) -> ParseResult<std::tuple<T,Ks ...>> {
        ParseResult<T> r1 = first(it);
        if(!r1)
            return Failure<std::tuple<T,Ks ...>>(it);
        ParseResult<std::tuple<Ks ...>> r2 = p2(r1.remaining);
        if(!r2)
            return Failure<std::tuple<T,Ks ...>>(it);
        return Success(std::tuple_cat(r1.value, r2.value), r2.remaining);
    };
}

//Choose first successful parser
template <typename T, typename K>
Parser<std::variant<T, K>> Alternate(const Parser<T>& first, const Parser<K>&  next) {
    return [=](const ParseIterator& it) -> ParseResult<std::variant<T, K>> { 
        ParseResult<T> r1 = first(it);
        if(r1)
            return Success<std::variant<T, K>>(r1.value, r1.remaining);
        ParseResult<K> r2 = next(r1.remaining);
        if(r2)
            return Success<std::variant<T, K>>(r2.value, r2.remaining);
        return Failure<std::variant<T, K>>(it);
    };
}
//TODO Varient not available in anything < c++17 so thats an issue
template <typename T, typename ... Ks>
Parser<std::variant<T, Ks...>> Alternate(const Parser<T>& first, const Parser<Ks>& ... next) {
    Parser<std::variant<Ks...>> p2 = Alternate(next ...);
    return [=](const ParseIterator& it) -> ParseResult<std::variant<T, Ks ...>> { 
        ParseResult<T> r1 = first(it);
        if(r1)
            return Success<std::variant<T, Ks ...>>(r1.value, r1.remaining);
        ParseResult<std::variant<Ks...>> r2 = p2(r1.remaining);
        if(r2)
            return Success<std::variant<T, Ks ...>>(std::move(r2.value), r2.remaining);
        return Failure<std::variant<T, Ks ...>>(it);
    };
}

//Repeat between [min, max] times
template <typename T>
Parser<std::vector<T>> Repeat(const Parser<T>& parser, size_t min, size_t max) {
    return [=](const ParseIterator& it) -> ParseResult<std::vector<T>> {
        std::vector<T> stack;
        stack.reserve(min);
        ParseResult<T> results;
        ParseIterator itc = it;
        size_t i{0};
        for(; i < max; i++) {
            results = parser(itc); //TODO Fix this (iterator must update each loop)
            if(results) {
                break;
            } else {
                stack.push_back(results.value);
                itc = results.remaining;
            }
        }
        if(i >= min && i < max) {
            return Success<std::vector<T>>(stack, results.remaining);
        } else {
            return Failure<std::vector<T>>(it);
        }
    };
} 

//Repeat between [min, max_uint] times
template <typename T>
Parser<std::vector<T>> Repeat(const Parser<T>& parser, size_t min) {
    return Repeat(parser, min, std::numeric_limits<size_t>::max());
}

//Repeat 0 or 1 times
template <typename T>
Parser<std::optional<T>> Optional(const Parser<T> parser) {
    return [=](const ParseIterator& it) -> ParseResult<std::optional<T>> {
        ParseResult<T> r = parser(it); //run parser
        if(r)
            return Success<std::optional<T>>(r.value, r.remaining); //success, gimme
        else   
            return Success<std::optional<T>>({}, it); //failure, gimme anyways with nothing
    };
}

//Read ahead, consuming no input, true if parser fails
template <typename T>
Parser<bool> Not(const Parser<T>& parser) {
    return [=](const ParseIterator& it) -> ParseResult<bool> {
        ParseResult<T> r = parser(it);
        if(!r)
            return Success<bool>(true, it);
        else
            return Failure<bool>(it);
    };
}

//Read ahead but do not consume input, true if the lookahead is found
template <typename T>
Parser<T> Lookahead(const Parser<T>& parser) {
    return [=](const ParseIterator& it) -> ParseResult<bool> {
        ParseResult<T> r = parser(it);
        if(r)
            return Success<T>(r.value, it);
        else
            return Failure<T>(it);
    };
}


//Convert the output of a parser from one type to another
template <typename T, typename K>
Parser<K> Map(const Parser<T>& parser, std::function<K(T)>& mapping) {
    return [=](const ParseIterator& it) -> ParseResult<K> {
        ParseResult<T> r = parser(it);
        if(r)
            return Success<K>(mapping(r.value), r.remaining);
        else
            return Failure<K>(it);
    };
} 

//Convert the output of a parser from one type to another converting failures to successes
template <typename T, typename K>
Parser<K> BiMap(const Parser<T>& parser, std::function<K(T)>& success, std::function<K(T)>& failure){
    return [=](const ParseIterator& it) -> ParseResult<K> {
        ParseResult<T> r = parser(it);
        if(r)
            return Success<K>(success(r.value), r.remaining);
        else
            return Success<K>(failure(r.value), it);
    };
}


//Get the first element from a sequence
template <typename K, typename ... Ts>
Parser<K> First(const Parser<std::tuple<K, Ts ...>>& parser) {
    return [=](const ParseIterator& it) -> ParseResult<K> {
        ParseResult<std::tuple<K, Ts ...>> r = parser(it);
        if(r)
            return Success<K>(std::get<0>(r.value), r.remaining);
        else 
            return Failure<K>(it);
    };
}

//Get the last element from a sequence
template <typename K, typename ... Ts>
Parser<K> Last(const Parser<std::tuple<Ts ..., K>>& parser) {
    return [=](const ParseIterator& it) -> ParseResult<K> {
        ParseResult<std::tuple<K, Ts ...>> r = parser(it);
        if(r)
            return Success<K>(std::get<sizeof...(Ts)>(r.value), r.remaining);
        else 
            return Failure<K>(it);
    };
}

//Get the middle element(s) from a sequence
template <typename T, typename T2, typename ... Ks>
Parser<std::tuple<Ks ...>> Between(const Parser<std::tuple<T, Ks ..., T2>>& parser) {
    return [=](const ParseIterator& it) -> ParseResult<std::tuple<Ks ...>> {
        ParseResult<std::tuple<T, Ks ..., T2>> r = parser(it);
        if(r)
            return Success<std::tuple<Ks ...>>(
                std::make_tuple(std::get<Ks>(r.value) ...),
                r.remaining
            );
        else 
            return Failure<std::tuple<Ks ...>>(it);
    };
}

//Utility parsers (premade combinations)
template <typename T>
Parser<T> OneOrMore(const Parser<T> parser) {
    return Repeat(parser, 1);
}

template <typename T>
Parser<T> ZeroOrMore(const Parser<T> parser) {
    return Repeat(parser, 0);
}

template <typename T, typename K>
Parser<T> Skip(const Parser<T> parser, const Parser<K> toSkip) {
    return Between(Sequence(Optional(toSkip), parser, Optional(toSkip))); //Maybe just Last(Sequence(Optional(toSkip), parser)); skipping only leading values
}

//TODO ensure return types are correct (clean up if allowed ie % operator would be nice to just get std::vector without separator) 
// Shorthands for DSL

//Left hand thing followed by right hand thing (shorthand for Sequence(lhs, rhs))
template <typename T, typename K>
Parser<std::tuple<T,K>> operator & (const Parser<T>& lhs, const Parser<K>& rhs) {
    return Sequence(lhs, rhs);
}

//Left hand thing or right hand thing (shorthand for Alternate(lhs, rhs))
template <typename T, typename K>
Parser<std::variant<T,K>> operator | (const Parser<T>& lhs, const Parser<K>& rhs) {
    return Alternate(lhs, rhs);
}

//Left hand thing separated by right hand thing (shorthand for Sequence(lhs, Repeat(Sequence(rhs, lhs), 0)))
template <typename T, typename K>
Parser<std::tuple<T, std::vector< std::tuple<K,T>>>> operator % (const Parser<T>& lhs, const Parser<K>& rhs) {
    return Sequence(lhs, Repeat(Sequence(rhs, lhs), 0));
}

//One or more repetitions (shorthand for Repeat(val, 1))
template <typename T>
Parser<std::vector<T>> operator + (const Parser<T>& val) {
    return OneOrMore(val);
}

//Zero or more repetitions (shorthand for Repeat(val, 0))
template <typename T>
Parser<std::vector<T>> operator * (const Parser<T>& val) {
    return ZeroOrMore(val);
}

//Exactly 0 or 1 repetitions (shorthand for Repeat(val, 0, 1))
template <typename T>
Parser<std::optional<T>> operator ~ (const Parser<T>& val) {
    return Optional(val);
}

//Not the thing that follows (shorthand for Not(val))
template <typename T>
Parser<bool> operator ! (const Parser<T>& val) {
    return Not(val);
}

//Not the thing that follows (shorthand for Not(val))
template <typename T, typename K>
Parser<T> operator ^ (const Parser<T>& val, const Parser<K>& skips) {
    return Skip(val, skips);
}

}
}
}

#endif