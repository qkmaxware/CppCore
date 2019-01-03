// Basic Includes
#include <gtest/gtest.h>
#include <iostream>

// Add Test Includes
#include "Tests.System.Text.String.hpp"
#include "Tests.System.Math.hpp"
#include "Tests.System.Io.Path.hpp"

// Other Includes

// Run Tests
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}