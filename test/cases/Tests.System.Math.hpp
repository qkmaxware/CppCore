#include "System.Math.hpp"

TEST(SystemMath, Clamp) {
    using namespace System::Math;
    EXPECT_EQ(Clamp(10, 2, 8), 8);
    EXPECT_EQ(Clamp(0, 2, 8), 2);
    EXPECT_EQ(Clamp(4, 2, 8), 4);
}

TEST(SystemMath, Clamp01) {
    using namespace System::Math;
    EXPECT_EQ(Clamp01(0.5), 0.5);
    EXPECT_EQ(Clamp01(1.2), 1);
    EXPECT_EQ(Clamp01(-0.2), 0);  
}

TEST(SystemMath, Lerp) {
    using namespace System::Math;
    EXPECT_EQ(Lerp(0,10, 0.5), 5);
    EXPECT_EQ(Lerp(0,10, 0), 0);
    EXPECT_EQ(Lerp(0,10, 1), 10);
    EXPECT_TRUE(Lerp(0,10, 0.4) < 5);
    EXPECT_TRUE(Lerp(0,10, 0.8) > 5);
}

TEST(SystemMath, MoveTowards) {
    using namespace System::Math;
    EXPECT_EQ(MoveTowards(5, 10, 2), 7);
    EXPECT_EQ(MoveTowards(-5, -10, 2), -7);
    EXPECT_EQ(MoveTowards(5, 10, 10), 10);
    EXPECT_EQ(MoveTowards(5, 10, 0), 5);
    EXPECT_EQ(MoveTowards(-5, -10, 10), -10);
    EXPECT_EQ(MoveTowards(-5, -10, 0), -5);
}

TEST(SystemMath, Repeat) {
    using namespace System::Math;
    EXPECT_EQ(Repeat(12, 10), 2);
    EXPECT_EQ(Repeat(-2, 10), 8);
    EXPECT_EQ(Repeat(5, 10), 5);
}

TEST(SystemMath, Round) {
    using namespace System::Math;
    EXPECT_EQ(Round(0.5, RoundingMode::HalfEven), 0);
    EXPECT_EQ(Round(0.8, RoundingMode::HalfEven), 1);
    EXPECT_EQ(Round(2.5, RoundingMode::HalfEven), 2);
    EXPECT_EQ(Round(3.5, RoundingMode::HalfEven), 4);

    EXPECT_EQ(Round(-0.5, RoundingMode::HalfEven), 0);
    EXPECT_EQ(Round(-0.8, RoundingMode::HalfEven), -1);
    EXPECT_EQ(Round(-2.5, RoundingMode::HalfEven), -2);
    EXPECT_EQ(Round(-3.5, RoundingMode::HalfEven), -4);
}

TEST(SystemMath, Abs) {
    using namespace System::Math;
    EXPECT_EQ(Abs(1.0), 1.0);
    EXPECT_EQ(Abs(-1.0), 1.0);
    EXPECT_EQ(Abs((long)1), (long)1);
    EXPECT_EQ(Abs((long)-1), (long)1);
}

TEST(SystemMath, Ceiling) {
    using namespace System::Math;
    EXPECT_EQ(Ceiling(0.8), 1);
    EXPECT_EQ(Ceiling(0.2), 1);
    EXPECT_EQ(Ceiling(2.6), 3);
}

TEST(SystemMath, Floor) {
    using namespace System::Math;
    EXPECT_EQ(Floor(0.8), 0);
    EXPECT_EQ(Floor(0.2), 0);
    EXPECT_EQ(Floor(2.6), 2);
}

TEST(SystemMath, Pow) {
    using namespace System::Math;
    EXPECT_EQ(Pow(2, 2), 4);
    EXPECT_EQ(Pow(3, 2), 9);
    EXPECT_EQ(Pow(2, 3), 8);
}

TEST(SystemMath, Sign) {
    using namespace System::Math;
    EXPECT_EQ(Sign((long)0), 0);
    EXPECT_EQ(Sign((long)3), 1);
    EXPECT_EQ(Sign((long)-3), -1);
}

TEST(SystemMath, Sqrt) {
    using namespace System::Math;
    EXPECT_EQ(Sqrt(4), 2);
}

TEST(SystemMath, Min) {
    using namespace System::Math;
    EXPECT_EQ(Min(8, 4, 5, 6), 4);
    EXPECT_EQ(Min(8, 4, 5, 6, -1), -1);
}

TEST(SystemMath, Max) {
    using namespace System::Math;
    EXPECT_EQ(Max(8, 4, 5, 6), 8);
    EXPECT_EQ(Max(8, 4, 5, 6, 10), 10);
}