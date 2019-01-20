#include "System.Text.Parsing.hpp"

TEST(SystemTextParsing, Always) {
    using namespace System::Text::Parsing;
    std::string pattern = "H";
    ParseResult<bool> res = Always()(pattern);
    EXPECT_TRUE(res.success);
}

TEST(SystemTextParsing, Never) {
    using namespace System::Text::Parsing;
    std::string pattern = "H";
    ParseResult<bool> res = Never()(pattern);
    EXPECT_FALSE(res.success);
}


TEST(SystemTextParsing, Char) {
    using namespace System::Text::Parsing;
    std::string pattern = "H";
    ParseResult<char> res = Char('H')(pattern);
    EXPECT_TRUE(res.success);
    res = Char('K')(pattern);
    EXPECT_FALSE(res.success);
}

TEST(SystemTextParsing, Range) {
    using namespace System::Text::Parsing;
    std::string pattern = "H";
    ParseResult<char> res = Range('A', 'Z')(pattern);
    EXPECT_TRUE(res.success);
    res = Range('a', 'z')(pattern);
    EXPECT_FALSE(res.success);
}

TEST(SystemTextParsing, CharIn) {
    using namespace System::Text::Parsing;
    std::string pattern = "H";
    ParseResult<char> res = CharIn({'h', 'H'})(pattern);
    EXPECT_TRUE(res.success);
    res = CharIn({'a', 'A'})(pattern);
    EXPECT_FALSE(res.success);
}

TEST(SystemTextParsing, NotChar) {
    using namespace System::Text::Parsing;
    std::string pattern = "H";
    ParseResult<char> res = NotChar('h')(pattern);
    EXPECT_TRUE(res.success);
    res = NotChar('H')(pattern);
    EXPECT_FALSE(res.success);
}

TEST(SystemTextParsing, Digit) {
    using namespace System::Text::Parsing;
    for(int i = 0; i <=9; i++) {
        std::string pattern = std::to_string(i);
        ParseResult<char> res = Digit(pattern);
        EXPECT_TRUE(res.success);
    }
    std::string failPattern = "foo";
    ParseResult<char> res = Digit(failPattern);
    EXPECT_FALSE(res.success);
}

TEST(SystemTextParsing, QuotedString) {
    using namespace System::Text::Parsing;

    std::string pattern = "\"bar\"";
    ParseResult<std::string> res = QuotedString(pattern);
    EXPECT_TRUE(res.success);

    pattern = "foo";
    res = QuotedString(pattern);
    EXPECT_FALSE(res.success);
}

TEST(SystemTextParsing, ExactString) {
    using namespace System::Text::Parsing;

    std::string pattern = "word";
    ParseResult<std::string> res = ExactString("word")(pattern);
    EXPECT_TRUE(res.success);

    pattern = "foo";
    res = ExactString("word")(pattern);
    EXPECT_FALSE(res.success);
}

TEST(SystemTextParsing, Skip) {
    using namespace System::Text::Parsing;

    std::string pattern = "    word";
    ParseResult<std::string> res = Skip(ExactString("word"), Whitespace)(pattern);
    EXPECT_TRUE(res.success);

    pattern = "word";
    res = Skip(ExactString("word"), Whitespace)(pattern);
    EXPECT_TRUE(res.success);


    pattern = "   foo";
    res = Skip(ExactString("word"), Whitespace)(pattern);
    EXPECT_FALSE(res.success);
}

TEST(SystemTextParsing, DecimalNumber) {
    using namespace System::Text::Parsing;

    std::string pattern = "14.125";
    ParseResult<double> res = DecimalNumber(pattern);
    EXPECT_TRUE(res.success);
    EXPECT_DOUBLE_EQ(res.value, 14.125);

    pattern = "-2.1";
    res = DecimalNumber(pattern);
    EXPECT_TRUE(res.success);
    EXPECT_DOUBLE_EQ(res.value, -2.1);

    pattern = "3e2";
    res = DecimalNumber(pattern);
    EXPECT_TRUE(res.success);
    EXPECT_DOUBLE_EQ(res.value, 3E2);

    pattern = "foobar";
    res = DecimalNumber(pattern);
    EXPECT_FALSE(res.success);
}