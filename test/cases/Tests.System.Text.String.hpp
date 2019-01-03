#include "System.Text.String.hpp"

TEST(SystemTextString, Length) {
    using namespace System::Text;
    String s("Hello World");
    EXPECT_EQ(s.Length(), 11);
    String s2;
    EXPECT_EQ(s2.Length(), 0);
    String s3(s);
    EXPECT_EQ(s3.Length(), 11);
    std::string test("test");
    String s4(test);
    EXPECT_EQ(s4.Length(), test.size());
}

TEST(SystemTextString, CharAt) {
    using namespace System::Text;
    String s("Hello");
    EXPECT_EQ(s[0], 'H');
    EXPECT_EQ(s[1], 'e');
    EXPECT_EQ(s[2], 'l');
    EXPECT_EQ(s[3], 'l');
    EXPECT_EQ(s[4], 'o');
}

TEST(SystemTextString, IndexOfChar) {
    using namespace System::Text;
    String s("Hello World");
    EXPECT_EQ(s.IndexOf('l'), 2);
    EXPECT_EQ(s.IndexOf('o'), 4);
    EXPECT_EQ(s.IndexOf('d'), 10);
    EXPECT_EQ(s.IndexOf('z'), -1);
}

TEST(SystemTextString, LastIndexOfChar) {
    using namespace System::Text;
    String s("Hello World");
    EXPECT_EQ(s.LastIndexOf('l'), 9);
    EXPECT_EQ(s.LastIndexOf('o'), 7);
    EXPECT_EQ(s.LastIndexOf('d'), 10);
    EXPECT_EQ(s.IndexOf('z'), -1);
}

TEST(SystemTextString, IndexOfString) {
    using namespace System::Text;
    String s("Hello World");
    EXPECT_EQ(s.IndexOf("lo"), 3);
    EXPECT_EQ(s.IndexOf("World"), 6);
}

TEST(SystemTextString, LastIndexOfString) {
    using namespace System::Text;
    String s("Hello World");
    EXPECT_EQ(s.LastIndexOf("l"), 9);
    EXPECT_EQ(s.LastIndexOf("lo"), 3);
}

TEST(SystemTextString, StartsWith) {
    using namespace System::Text;
    String s("Hello World");
    EXPECT_TRUE(s.StartsWith("Hello"));
    EXPECT_FALSE(s.StartsWith("World"));
    EXPECT_FALSE(s.StartsWith("Hello World Foo"));
}

TEST(SystemTextString, EndsWith) {
    using namespace System::Text;
    String s("Hello World");
    EXPECT_TRUE(s.EndsWith("World"));
    EXPECT_FALSE(s.EndsWith("Hello"));
    EXPECT_FALSE(s.EndsWith("Hello World Foo"));
}

TEST(SystemTextString, IsEmpty) {
    using namespace System::Text;
    String empty("");
    String notEmpty(" ");
    EXPECT_TRUE(empty.IsEmpty());
    EXPECT_FALSE(notEmpty.IsEmpty());
}

TEST(SystemTextString, IsEmptyOrWhitespace) {
    using namespace System::Text;
    String empty("");
    String stillEmpty("    \t\n");
    String notEmpty(" \n\t\r i");
    ASSERT_TRUE(String::Whitespace.Length() >= 0);
    ASSERT_TRUE(String::Whitespace.IndexOf('\t') >= 0);
    ASSERT_TRUE(String::Whitespace.IndexOf('\n') >= 0);
    ASSERT_TRUE(String::Whitespace.IndexOf('\r') >= 0);
    ASSERT_TRUE(String::Whitespace.IndexOf(' ') >= 0);

    EXPECT_TRUE(empty.IsEmptyOrWhitespace());
    EXPECT_TRUE(stillEmpty.IsEmptyOrWhitespace());
    EXPECT_FALSE(notEmpty.IsEmptyOrWhitespace());
}

TEST(SystemTextString, ToUpperCase) {
    using namespace System::Text;
    String lower("aBcDeFg");
    lower.ToUpperCase();
    String upper("ABCDEFG");
    EXPECT_EQ(lower, upper);
}

TEST(SystemTextString, ToLowerCase) {
    using namespace System::Text;
    String upper("aBcDeFg");
    upper.ToLowerCase();
    String lower("abcdefg");
    EXPECT_EQ(lower, upper);
}

TEST(SystemTextString, ToggleCase) {
    using namespace System::Text;
    String val("aBcDeFg");
    val.ToggleCase();
    String toggle("AbCdEfG");
    EXPECT_EQ(val, toggle);
}

TEST(SystemTextString, LeftTrim) {
    using namespace System::Text;
    String val("     Hello World");
    val.LeftTrim();
    EXPECT_EQ(val.Length(), 11);
    String val2("zzwxHello World");
    val2.LeftTrim("zwx");
    EXPECT_EQ(val.Length(), 11);
}

TEST(SystemTextString, RightTrim) {
    using namespace System::Text;
    String val("Hello World    ");
    val.RightTrim();
    EXPECT_EQ(val.Length(), 11);
    String val2("Hello Worldzzwx");
    val2.RightTrim("zwx");
    EXPECT_EQ(val.Length(), 11);
}

TEST(SystemTextString, Trim) {
    using namespace System::Text;
    String val("   Hello World   ");
    val.Trim();
    EXPECT_EQ(val.Length(), 11);
    String val2("xwzzHello Worldzzwx");
    val2.RightTrim("zwx");
    EXPECT_EQ(val.Length(), 11);
}

TEST(SystemTextString, LeftPad) {
    using namespace System::Text;
    String val("Hello World");
    val.LeftPad(10, ' ');
    EXPECT_EQ(val.Length(), 11);
    val.LeftPad(14, ' ');
    EXPECT_EQ(val.Length(), 14);
}

TEST(SystemTextString, RightPad) {
    using namespace System::Text;
    String val("Hello World");
    val.RightPad(10, ' ');
    EXPECT_EQ(val.Length(), 11);
    val.RightPad(14, ' ');
    EXPECT_EQ(val.Length(), 14);
}

TEST(SystemTextString, Slice) {
    using namespace System::Text;
    String val("Hello World");
    EXPECT_EQ(val.Slice(1,1)[0], 'e');
    String hello = val.Slice(0,4);
    String world = val.Slice(6,10);
    EXPECT_EQ(hello.Length(), 5);
    EXPECT_EQ(hello, String("Hello"));
    EXPECT_EQ(world.Length(), 5);
    EXPECT_EQ(world, String("World"));

    String olleh = val.Slice(4, 0);
    EXPECT_EQ(olleh.Length(), 5);
    EXPECT_EQ(olleh, String("olleH"));
}

TEST(SystemTextString, StringCompareEquality) {
    using namespace System::Text;
    String val  ("Hello World");
    String val2 ("Foo Bar");
    EXPECT_TRUE(val == val);
    EXPECT_TRUE(val2 == val2);
    EXPECT_FALSE(val == val2);
    EXPECT_FALSE(val2 == val);
}

TEST(SystemTextString, StringCompareInequality) {
    using namespace System::Text;
    String val  ("Hello World");
    String val2 ("Foo Bar");
    EXPECT_FALSE(val != val);
    EXPECT_FALSE(val2 != val2);
    EXPECT_TRUE(val != val2);
    EXPECT_TRUE(val2 != val);
}