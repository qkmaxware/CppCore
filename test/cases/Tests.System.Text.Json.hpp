#include "System.Text.Json.hpp"

TEST(SystemTextJson, Null) {
    using namespace System::Text::Json;

    std::string correct_json = "null";
    std::string failure_json = "true";

    ParseResult<JsonNullType> val = JsonNull(correct_json);
    EXPECT_TRUE(val.success);

    val = JsonNull(failure_json);
    EXPECT_FALSE(val.success);
}

TEST(SystemTextJson, True) {
    using namespace System::Text::Json;

    std::string correct_json = "true";
    std::string failure_json = "false";

    ParseResult<JsonBoolType> val = JsonBooleanTrue(correct_json);
    EXPECT_TRUE(val.success);

    val = JsonBooleanTrue(failure_json);
    EXPECT_FALSE(val.success);
}

TEST(SystemTextJson, False) {
    using namespace System::Text::Json;

    std::string correct_json = "false";
    std::string failure_json = "true";

    ParseResult<JsonBoolType> val = JsonBooleanFalse(correct_json);
    EXPECT_TRUE(val.success);

    val = JsonBooleanFalse(failure_json);
    EXPECT_FALSE(val.success);
}

TEST(SystemTextJson, Bool) {
    using namespace System::Text::Json;

    std::string correct_json = "false";
    std::string correct_json2 = "true";
    std::string failure_json = "null";

    ParseResult<JsonBoolType> val = JsonBoolean(correct_json);
    EXPECT_TRUE(val.success);

    val = JsonBoolean(correct_json2);
    EXPECT_TRUE(val.success);

    val = JsonBoolean(failure_json);
    EXPECT_FALSE(val.success);
}

TEST(SystemTextJson, Number) {
    using namespace System::Text::Json;

    std::string correct_json = "12.5";
    std::string failure_json = "true";

    ParseResult<JsonNumberType> val = JsonNumber(correct_json);
    EXPECT_TRUE(val.success);

    val = JsonNumber(failure_json);
    EXPECT_FALSE(val.success);
}

TEST(SystemTextJson, String) {
    using namespace System::Text::Json;

    std::string correct_json = "\"Json String\"";
    std::string failure_json = "null";

    ParseResult<JsonStringType> val = JsonString(correct_json);
    EXPECT_TRUE(val.success);

    val = JsonString(failure_json);
    EXPECT_FALSE(val.success);
}
