#ifndef _SYSTEM_TEXT_HPP
#define _SYSTEM_TEXT_HPP

#include "System.hpp"
#include <iostream>

namespace System {
namespace Text {

using StringChar = char;

// Based on
// https://docs.oracle.com/javase/7/docs/api/java/lang/String.html
class String : public System::Object {
    private:
        StringChar* data;
        uint32 length;

    public:
        static const String Digits;
        static const String Lowercase;
        static const String Uppercase;
        static const String Alpha;
        static const String HexDigits;
        static const String OctDigits;
        static const String Whitespace;

        String();
        String(StringChar c);
        String(StringChar c, uint32 length);
        String(const StringChar* string);
        String(const String& string);
        String(const std::string& cstring);
        virtual ~String();

        static bool IsWhitespace(StringChar c);

        uint32 Length() const;
        StringChar CharAt(uint32 index) const;
        int32 IndexOf(StringChar c) const;
        int32 LastIndexOf(StringChar c) const;
        int32 IndexOf(const String& other) const;
        int32 LastIndexOf(const String& other) const;
        bool StartsWith(const String& other) const;
        bool EndsWith(const String& other) const;
        bool IsEmpty() const;
        bool IsEmptyOrWhitespace() const;
        void ToUpperCase();
        void ToLowerCase();
        void ToggleCase();
        String& LeftTrim(const String& chars = String::Whitespace);
        String& RightTrim(const String& chars = String::Whitespace);
        String& Trim(const String& chars = String::Whitespace);
        String& LeftPad(uint32 length, StringChar pad = ' ');
        String& RightPad(uint32 length, StringChar pad = ' ');
        static String ValueOf(char c);
        static String ValueOf(double c);
        static String ValueOf(long c);
        static String ValueOf(const System::Object& c);
        //String Format() const;
        //std::vector<String> Split(char delim) const;
        String Slice(uint32 start, uint32 end) const;
        virtual std::string ToString() const;
        virtual std::uintptr_t GetHashCode() const;

        operator std::string() const;

        friend std::ostream& operator << (std::ostream& stream, const String& data);
        friend std::istream& operator >> (std::istream& stream, String& data);

        StringChar operator [] (uint32 index) const;
        StringChar& operator [] (uint32 index);

        String& operator = (const String& s);
        String& operator += (const String& s);

        friend String operator + (const String& lhs, const String& rhs);
        friend String operator + (const String& lhs, StringChar rhs);
        friend String operator + (const String& lhs, const char* rhs);
        friend String operator + (StringChar lhs, const String& rhs);
        friend String operator + (const char* lhs, const String& rhs);

        friend bool operator == (const String& lhs, const String& rhs);
        friend bool operator == (const String& lhs, StringChar rhs);
        friend bool operator == (const String& lhs, const char* rhs);
        friend bool operator == (StringChar lhs, const String& rhs);
        friend bool operator == (const char* lhs, const String& rhs);

        friend bool operator != (const String& lhs, const String& rhs);
        friend bool operator != (const String& lhs, StringChar rhs);
        friend bool operator != (const String& lhs, const char* rhs);
        friend bool operator != (StringChar lhs, const String& rhs);
        friend bool operator != (const char* lhs, const String& rhs);
};

}
}

#endif