#include "halftone_images.cpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>
using namespace std;

TEST(HalftoneImageTests, OperatorCheck) {
    HalftoneImage<short> h(3, 3, false);
    h(0, 2) = 3;
    EXPECT_EQ(3, h(0, 2));

}

TEST(HalftoneImageTests, ExceptionCheck) {
    EXPECT_ANY_THROW(HalftoneImage<short> h(3, -3, false));
    EXPECT_ANY_THROW(HalftoneImage<short> h(-3, 4, true));
}

TEST(HalftoneImageTests, ConstructorCheck) {
    HalftoneImage<bool> h1(2, 2, false);
    h1(0, 0) = 0; h1(0, 1) = 1; h1(1, 0) = 1; h1(1, 1) = 0;
    bool* data = new bool[4] {0,1,1,0 };
    HalftoneImage<bool> h2(2, 2, data);
    cout << h1;
    cout << h2;
    EXPECT_TRUE(h1 == h2);
    EXPECT_FALSE(h1 != h2);
}
