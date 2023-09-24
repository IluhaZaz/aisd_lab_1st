#include "halftone_images.cpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>
using namespace std;
#define EPSILON 0.0001

TEST(HalftoneImageTests, SwapCheck) {
    short* data1 = new short[4] {1, 2, 3, 4 };
    HalftoneImage<short> h1(2, 2, data1);
    short* data2 = new short[4] {5, 6, 7, 8 };
    HalftoneImage<short> h2(2, 2, data2);
    cout << h1;
    cout << h2;
    swap(h1, h2);
    cout << h1;
    cout << h2;
}


TEST(HalftoneImageTests, ConstructorCheck) {
    HalftoneImage<bool> h1(2, 2, false);
    h1(0, 0) = 0; h1(0, 1) = 1; h1(1, 0) = 1; h1(1, 1) = 0;
    bool* data = new bool[4] {0, 1, 1, 0 };
    HalftoneImage<bool> h2(2, 2, data);
    EXPECT_TRUE(h1 == h2);
    EXPECT_FALSE(h1 != h2);

    HalftoneImage<bool> h3(2, 2, false);
    h3(0, 0) = 0; h3(0, 1) = 1; h3(1, 0) = 1; h3(1, 1) = 0;
    HalftoneImage<bool> h4(h3);
    EXPECT_EQ(h3, h4);

}

TEST(HalftoneImageTests, OperatorCheck) {
    HalftoneImage<short> h(3, 3, false);
    h(0, 2) = 3;
    EXPECT_EQ(3, h(0, 2));

    short* data1 = new short[4] {10, 5, 3, 0 };
    HalftoneImage<short> h1(2, 2, data1);
    short* data2 = new short[4] {-5, 2, 1, -100 };
    HalftoneImage<short> h2(2, 2, data2);
    short* data3 = new short[4] {5, 7, 4, -100 };
    HalftoneImage<short> h3(2, 2, data3);
    EXPECT_TRUE(h3 == h1 + h2);

    short* data4 = new short[4] {-50, 10, 3, 0 };
    HalftoneImage<short> h4(2, 2, data4);
    EXPECT_TRUE(h4 == h1 * h2);
    
    data3 = new short[4] {5, 7, 4, std::numeric_limits<short>::max() -100 };
    HalftoneImage<short> h5(2, 2, data3);
    data4 = new short[4] {5, 7, 4, 300};
    HalftoneImage<short> h6(2, 2, data3);
    EXPECT_EQ(std::numeric_limits<short>::max(), (h5 + h6)(1, 1));

    short* data5 = new short[4] {1, 2, 3, 4 };
    HalftoneImage<short> h7(2, 2, data5);
    HalftoneImage<short> h8 = HalftoneImage<short>(2, 2, data5);
    EXPECT_EQ(h7, h8);
}

TEST(HalftoneImageTests, ExceptionCheck) {
    EXPECT_ANY_THROW(HalftoneImage<short> h(3, -3, false));
    EXPECT_ANY_THROW(HalftoneImage<short> h(-3, 4, true));

    short* data1 = new short[6] {10, 5, 3, 0, 3, 4};
    HalftoneImage<short> h1(3, 2, data1);
    short* data2 = new short[4] {-5, 2, 1, -100 };
    HalftoneImage<short> h2(2, 2, data2);
    EXPECT_ANY_THROW(h1 + h2);
    EXPECT_ANY_THROW(h1 * h2);
}

TEST(HalftoneImageTests, CountFillFactorCheck) {
    HalftoneImage<short> h(3, 3, false);
    EXPECT_EQ(0, h.count_fill_factor());
    
    short* data = new short[4] {10000, 20000, 30000, 4000 };
    HalftoneImage<short> h2(2, 2, data);
    EXPECT_NEAR(0.2882961, h2.count_fill_factor(), EPSILON);
}



