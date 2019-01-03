#include "System.Text.String.hpp"
#include <string>
#include <locale>
#include <codecvt>

namespace System {
namespace Text {

String::String() : data(nullptr), length(0) {}

String::String(StringChar c) : data(new StringChar(c)), length(1) {}

String::String(StringChar c, uint32 length) : data(new StringChar[length]), length(length) {
    for(uint32 i = 0; i < Length(); i++) {
        data[i] = c;
    }
}

String::String(const StringChar* str) : data(nullptr), length(0) {
    if(str){
        uint32 n = 0;
        while(str[n]){
            n++;
        }
        length = n;
        data = new StringChar[n];
        for(uint32 i = 0; i < n; i++)
            data[i] = str[i];
    }
}

String::String(const String& s): data(new StringChar[s.length]), length(s.length) {
    for(uint32 i = 0; i < length; i++)
        data[i] = s[i];
}

String::String(const std::string& cstring) : data(new StringChar[cstring.length()]), length(cstring.length()){
    for(uint32 i = 0; i < length; i++)
        data[i] = cstring[i];
}

String::~String() {
    if(data != nullptr)
        delete[] data;
}

bool String::IsWhitespace(StringChar c) {
    return (String::Whitespace.IndexOf(c) >= 0);
}

const String String::Digits = "0123456789";
const String String::Lowercase = "abcdefghijklmnopqrstuvwxyz";
const String String::Uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const String String::Alpha = String(String::Lowercase) + String::Uppercase;
const String String::HexDigits = "0123456789abcdefABCDEF";
const String String::OctDigits = "01234567";
const String String::Whitespace = " \f\n\r\t\v";

uint32 String::Length() const {
    return length;
}

StringChar String::CharAt(uint32 index) const {
    return data[index];
}

int32 String::IndexOf(StringChar c) const {
    for(uint32 i = 0; i < length; i++)
        if(data[i] == c)
            return static_cast<int32>(i);
    return -1;
}

int32 String::LastIndexOf(StringChar c) const {
    for(uint32 i = Length(); i > 0; i--)
        if(data[i - 1] == c)
            return static_cast<int32>(i - 1);
    return static_cast<int32>(-1);
}

int32 String::IndexOf(const String& other) const {
    if(other.Length() > Length())
        return -1;
    for(uint32 i = 0; i < (Length() - (other.Length() - 1)); i++){
        if(data[i] == other[0]){
            bool found{true};
            for(uint32 j = 0; j < other.Length(); j++){
                if(data[i + j] != other[j]){
                    found = false;
                    break;
                }
            }
            if(found)
                return static_cast<int32>(i);
        }
    }
    return -1;
}

int32 String::LastIndexOf(const String& other) const {
    if(other.Length() > Length())
        return -1;
    int32 index {-1};
    for(uint32 i = 0; i < (Length() - (other.Length() - 1)); i++){
        if(data[i] == other[0]){
            bool found{true};
            for(uint32 j = 0; j < other.Length(); j++){
                if(data[i + j] != other[j]){
                    found = false;
                    break;
                }
            }
            if(found)
                index = static_cast<int32>(i);
        }
    }
    return index;
}

bool String::StartsWith(const String& other) const {
    if (Length() >= other.Length()) {
        for(uint32 i = 0; i < other.Length(); i++)
            if(other[i] != data[i])
                return false;
        return true;
    } else {
        return false;
    }
}

bool String::EndsWith(const String& other) const {
    if (Length() >= other.Length()) {
        uint32 offset = Length() - other.Length();
        for(uint32 i = 0; i < other.Length(); i++){
            if(data[offset + i] != other[i])
                return false;
        }
        return true;
    } else {
        return false;
    }
}

bool String::IsEmpty() const {
    return length == 0 || data == nullptr;
}

bool String::IsEmptyOrWhitespace() const {
    if(IsEmpty())
        return true;
    for(uint32 i = 0; i < Length(); i++) {
        if(String::Whitespace.IndexOf(data[i]) < 0) { //Char is not whitespace
            return false;
        }
    }
    return true;
}

void String::ToUpperCase() {
    for(uint32 i = 0; i < Length(); i++) {
        int32 charidx = String::Lowercase.IndexOf(data[i]);
        if(charidx != -1){
            data[i] = String::Uppercase[charidx];
        }
    }
}

void String::ToLowerCase() {
    for(uint32 i = 0; i < Length(); i++) {
        int32 charidx = String::Uppercase.IndexOf(data[i]);
        if(charidx != -1){
            data[i] = String::Lowercase[charidx];
        }
    }
}

void String::ToggleCase() {
    for(uint32 i = 0; i < Length(); i++) {
        //Convert upper to lower
        int32 charidx = String::Uppercase.IndexOf(data[i]);
        if(charidx != -1){
            data[i] = String::Lowercase[charidx];
            continue;
        }
        //Convert lower to upper
        charidx = String::Lowercase.IndexOf(data[i]);
        if(charidx != -1){
            data[i] = String::Uppercase[charidx];
        }
    }
}

String& String::LeftTrim(const String& chars) {
    //Find first non-whitespace index
    uint32 startidx{0};
    for(uint32 i = 0; i < Length(); i++) {
        if(String::Whitespace.IndexOf(data[i]) == -1){ //Char is not whitespace
            startidx = i;
            break;
        }
    }
    //Create new array
    uint32 nl = Length() - startidx;
    StringChar* str = new StringChar[nl];
    uint32 cpidx{0};
    //Copy
    for(uint32 j = startidx; j < Length(); j++){
        str[cpidx++] = data[j];
    }
    //Cleanup
    delete[] data;
    data = str;
    length = nl;
    return *this;
}

String& String::RightTrim(const String& chars) {
    //Find lst non-whitespace index
    uint32 endidx{Length()};
    for(uint32 i = Length() - 1; i >= 0; i--) {
        if(String::Whitespace.IndexOf(data[i]) == -1){ //Char is not whitespace
            endidx = i + 1;
            break;
        }
    }
    //Create new array
    uint32 nl = endidx;
    StringChar* str = new StringChar[nl];
    uint32 cpidx{0};
    //Copy
    for(uint32 j = 0; j < nl; j++){
        str[cpidx++] = data[j];
    }
    //Cleanup
    delete[] data;
    data = str;
    length = nl;
    return *this;
}

String& String::Trim(const String& chars) {
    LeftTrim(chars);
    RightTrim(chars);
    return *this;
}

String& String::LeftPad(uint32 length, StringChar pad) {
    if(Length() >= length)
        return *this;
    uint32 diff = length - Length();
    StringChar* str = new StringChar[length];
    for(uint32 i = 0; i < diff; i++) {
        str[i] = pad;
    }
    for(uint32 i = 0; i < Length(); i++){
        str[diff + i] = data[i];
    }
    delete[] data;
    this->data = str;
    this->length = length;
    return *this;
}

String& String::RightPad(uint32 length, StringChar pad) {
    if(Length() >= length)
        return *this;
    uint32 diff = length - Length();
    StringChar* str = new StringChar[length];
    for(uint32 i = 0; i < Length(); i++){
        str[i] = data[i];
    }
    for(uint32 i = 0; i < diff; i++) {
        str[Length() + i] = pad;
    }
    delete[] data;
    this->data = str;
    this->length = length;
    return *this;
}

String String::ValueOf(char c) { 
    return String(std::to_string(c)); 
}
String String::ValueOf(double c) {
    return String(std::to_string(c)); 
}
String String::ValueOf(long c) {
    return String(std::to_string(c));
}
String String::ValueOf(const System::Object& c) {
    return String(c.ToString());
}

String String::Slice(uint32 start, uint32 end) const {
    //Slicing an empty string will always result in an empty string
    if(Length() == 0)
        return String();

    //Bounds checking [0, Length()] for both indices
    if(start >= Length())
        start = Length() - 1;
    if(end >= Length())
        end = Length() - 1;

    //Single character slice (start == end == data[start])
    if(start == end)
        return String(data[start]);

    //Multi character slice
    bool reverse { end < start };
    uint32 length = (reverse ? start - end : end - start) + 1;
    uint32 i { 0 };
    String s(' ', length);
    while(i < length) {
        s[ i++ ] = data[start];
        start += reverse ? - 1 : 1;
    }

    return s;
}

std::string String::ToString() const {
    return static_cast<std::string>(*this);
}

std::uintptr_t String::GetHashCode() const {
    int hash = 7;
    for (uint32 i = 0; i < length; i++) {
        hash = hash*31 + CharAt(i);
    }
    return hash;
}

String::operator std::string() const {
    return std::string(this->data);
}

std::ostream& operator << (std::ostream& stream, const String& data) {
    if(data.Length() > 0){
        for(uint32 i = 0; i < data.Length(); i++)
            stream << data[i];        
    }
    return stream;
}
std::istream& operator >> (std::istream& stream, String& data) {
    std::string str;
    stream >> str;
    data = String(str);
    return stream;
}

StringChar String::operator [] (uint32 index) const {
    return CharAt(index);
}

StringChar& String::operator [] (uint32 index) {
    return data[index];
}

String& String::operator = (const String& s) {
    if(this == &s)
        return *this;
    delete[] data;
    length = s.Length();
    data = new StringChar[length];
    for(uint32 i = 0; i < length; i++)
        data[i] = s[i];
    return *this;
}

String& String::operator += (const String& s) {
    uint32 len = length + s.Length();
    StringChar* str = new StringChar[len];

    for(uint32 i = 0; i < length; i++)
        str[i] = data[i];
    for(uint32 i = 0; i < s.Length(); i++)
        str[length+i] = s[i];   

    delete[] data;
    length = len;
    data = str;
    return *this;
}

String operator + (const String& lhs, const String& rhs) {
    uint32 len = lhs.Length() + rhs.Length();
    StringChar* str = new StringChar[len];

    for(uint32 i = 0; i < lhs.Length(); i++)
        str[i] = lhs[i];
    for(uint32 i = 0; i < rhs.Length(); i++)
        str[lhs.Length()+i] = rhs[i];  

    return String(str); 
}
String operator + (const String& lhs, StringChar rhs) {
    uint32 len = lhs.Length() + 1;
    StringChar* str = new StringChar[len];

    for(uint32 i = 0; i < lhs.Length(); i++)
        str[i] = lhs[i];
    str[lhs.Length()+1] = rhs;  

    return String(str); 
}
String operator + (const String& lhs, const char* rhs) {
    return lhs + String(rhs);
}
String operator + (StringChar lhs, const String& rhs) {
    uint32 len = rhs.Length() + 1;
    StringChar* str = new StringChar[len];

    str[0] = lhs;  
    for(uint32 i = 0; i < rhs.Length(); i++)
        str[i + 1] = rhs[i];
    

    return String(str); 
}
String operator + (const char* lhs, const String& rhs) {
    return String(lhs) + rhs;
}

bool operator == (const String& lhs, const String& rhs) {
    if(lhs.Length() != rhs.Length())
        return false;
    for(uint32 i = 0; i < lhs.Length(); i++)
        if(lhs[i] != rhs[i])
            return false;
    return true;
}
bool operator == (const String& lhs, StringChar rhs) {
    if(lhs.Length() != 1)
        return false;
    if(lhs[0] != rhs)
        return false;
    else
        return true;
}
bool operator == (const String& lhs, const char* rhs) {
    return lhs == String(rhs);
}
bool operator == (StringChar lhs, const String& rhs) {
    if(rhs.Length() != 1)
        return false;
    if(rhs[0] != lhs)
        return false;
    else
        return true;
}
bool operator == (const char* lhs, const String& rhs) {
    return String(lhs) == rhs;
}

bool operator != (const String& lhs, const String& rhs) {
    return !(lhs == rhs);
}
bool operator != (const String& lhs, StringChar rhs) {
    return !(lhs == rhs);
}
bool operator != (const String& lhs, const char* rhs) {
    return !(lhs == rhs);
}
bool operator != (StringChar lhs, const String& rhs) {
    return !(lhs == rhs);
}
bool operator != (const char* lhs, const String& rhs) {
    return !(lhs == rhs);
}

}
}