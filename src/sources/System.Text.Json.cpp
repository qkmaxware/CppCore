#include "System.Text.Json.hpp"

namespace System {
namespace Text {
namespace Json {

using namespace System::Text::Parsing;

//Parse Json NULL
const Parser<JsonNullType> JsonNull = Skip(ExactString("null"), Whitespace);

//Parse Json Number
const Parser<JsonNumberType> JsonNumber = Skip(DecimalNumber, Whitespace);

//Parse Json String
const Parser<JsonStringType> JsonString = Skip(QuotedString, Whitespace);

//Parse Json Boolean
const Parser<JsonBoolType> JsonBooleanTrue = Map<std::string, JsonBoolType>(
    Skip(ExactString("true"), Whitespace), [](std::string& str) -> JsonBoolType { return true; }
);
const Parser<JsonBoolType> JsonBooleanFalse = Map<std::string, JsonBoolType>(
    Skip(ExactString("false"), Whitespace), [](std::string& str) -> JsonBoolType { return false; }
);
const Parser<JsonBoolType> JsonBoolean = Map<AlternativeType<JsonBoolType,JsonBoolType>, JsonBoolType>(
    Alternate(JsonBooleanTrue, JsonBooleanFalse),
    [](AlternativeType<JsonBoolType,JsonBoolType>& val) -> JsonBoolType {
        if(std::get<0>(val).has_value()) {
            return std::get<0>(val).value();
        } else {
            return std::get<1>(val).value();
        }
    }
);

//Parse Json Array
const Parser<JsonArrayType> JsonArray = 
Between<char, std::vector<std::any>, char>(
    Sequence(
        Skip(Char('['), Whitespace),
        Map<std::optional<std::vector<std::any>>, std::vector<std::any>> (
            Optional(
                SeparatedWith(
                    Skip(JsonValue, Whitespace), 
                    Skip(Char(','), Whitespace)
                )
            ),
            [](std::optional<std::vector<std::any>>& res) -> std::vector<std::any> {
                if(res.has_value()) {
                    return res.value();
                } else {
                    std::vector<std::any> v;
                    return v;
                }
            }
        ),
        Skip(Char(']'), Whitespace)
    )
);

//Parse Json Object
const Parser<JsonObjectType> JsonObject =
Between(
    Sequence(
        Skip(Char('{'), Whitespace),
        Map<std::optional<std::vector<std::tuple<std::string, char, std::any>>>, std::map<std::string, std::any>> (
            Optional(
                SeparatedWith(
                    Sequence(
                        Skip(JsonString, Whitespace),
                        Skip(Char(':'), Whitespace), 
                        Skip(JsonValue, Whitespace)
                    ),
                    Skip(Char(','), Whitespace)
                )
            ),
            [](std::optional<std::vector<std::tuple<std::string, char, std::any>>>& res) -> std::map<std::string, std::any> {
                std::map<std::string, std::any> mp;
                if(!res.has_value())
                    return mp;
                auto& vec = res.value();
                for(auto x : vec) {
                    mp[std::get<0>(x)] = std::get<2>(x);
                }
                return mp;
            }
        ),
        Skip(Char('}'), Whitespace)
    )
);

const Parser<JsonValueType> JsonValue = 
Map<
    AlternativeType<
        std::string,
        double,
        bool,
        std::vector<std::any>,
        std::map<std::string, std::any>,
        std::string
    >, 
    std::any 
> (
    Alternate(
        JsonString,
        JsonNumber,
        JsonBoolean,
        JsonArray,
        JsonObject,
        JsonNull
    ),
    [](
        AlternativeType<
            std::string,
            double,
            bool,
            std::vector<std::any>,
            std::map<std::string, std::any>,
            std::string
        >& res
    ) -> std::any {
        //String
        if(std::get<0>(res).has_value()) {
            return std::any(std::get<0>(res).value());
        } 
        //Number
        else if(std::get<1>(res).has_value()) {
            return std::any(std::get<1>(res).value());
        }
        //Bool
        else if(std::get<2>(res).has_value()) {
            return std::any(std::get<2>(res).value());
        }
        //Array
        else if(std::get<3>(res).has_value()) {
            return std::any(std::get<3>(res).value());
        }
        //Object
        else if(std::get<4>(res).has_value()) {
            return std::any(std::get<4>(res).value());
        }
        //Null
        else {
            return std::any(std::string("null"));
        }
    }
);


}
}
}