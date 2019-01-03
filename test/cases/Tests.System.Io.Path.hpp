#include "System.Io.Path.hpp"

TEST(SystemIoPath, CurrentDirectory) {
    using namespace System::Io;
    try {
        Path::CurrentDirectory();
        EXPECT_TRUE(true);
    } catch(...) {
        EXPECT_TRUE(false);
    }
}
