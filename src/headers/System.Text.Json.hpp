#ifndef _SYSTEM_TEXT_JSON_HPP
#define _SYSTEM_TEXT_JSON_HPP

#include "System.Text.Parsing.hpp"
#include <any>

namespace System {
namespace Text {
namespace Json {

using namespace System::Text::Parsing;

//Parse any Json value'd type
using JsonValueType = std::any;
extern const Parser<JsonValueType> JsonValue;

//Parse Json NULL
using JsonNullType = std::string;
extern const Parser<JsonNullType> JsonNull;

//Parse Json Number
using JsonNumberType = double;
extern const Parser<JsonNumberType> JsonNumber;

//Parse Json String
using JsonStringType = std::string;
extern const Parser<JsonStringType> JsonString;

//Parse Json Boolean
using JsonBoolType = bool;
extern const Parser<JsonBoolType> JsonBooleanTrue;
extern const Parser<JsonBoolType> JsonBooleanFalse;
extern const Parser<JsonBoolType> JsonBoolean;

//Parse Json Array
using JsonArrayType = std::vector<JsonValueType>;
extern const Parser<JsonArrayType> JsonArray;

//Parse Json Object
using JsonObjectType = std::map<JsonStringType, JsonValueType>;
extern const Parser<JsonObjectType> JsonObject;

}
}
}

#endif
