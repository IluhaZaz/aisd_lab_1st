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
    cout << endl;
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

TEST(HalftoneImageTests, OperatorCheck2) {
    short* data1 = new short[4] {10, 5, 3, 100 };
    HalftoneImage<short> h1(2, 2, data1);
    short* data2 = new short[4] {15, 10, 8, 105 };
    HalftoneImage<short> h2(2, 2, data2);
    EXPECT_TRUE(h1 + 5 == h2);

    short* data3 = new short[4] {10, 5, 3, 100 };
    HalftoneImage<short> h3(2, 2, data3);
    short* data4 = new short[4] {30, 15, 9, 300 };
    HalftoneImage<short> h4(2, 2, data4);
    EXPECT_TRUE(h3 *3 == h4);

    bool* data5 = new bool[4] {1, 0, 0, 1 };
    HalftoneImage<bool> h5(2, 2, data5);
    bool* data6 = new bool[4] {1, 1, 1, 1};
    HalftoneImage<bool> h6(2, 2, data6);
    EXPECT_TRUE(h5 + 1 == h6);

    char* data7 = new char[4] {'a', 'b', 'c', 'd'};
    HalftoneImage<char> h7(2, 2, data7);
    char* data8 = new char[4] {'k', 'l', 'm', 'n'};
    HalftoneImage<char> h8(2, 2, data8);
    EXPECT_TRUE(h7 + 10 == h8);
}

TEST(HalftoneImageTests, OperatorCheck3) {
    short* data1 = new short[4] {10, 5, 3, 100 };
    HalftoneImage<short> h1(2, 2, data1);
    short* data2 = new short[4] {30, 15, 9, 300 };
    HalftoneImage<short> h2(2, 2, data2);
    EXPECT_TRUE(h1 * 3 == h2);

    short* data3 = new short[4] {10, 5, 3, 100 };
    HalftoneImage<short> h3(2, 2, data3);
    HalftoneImage<short> h4 = !h3;
    EXPECT_EQ(h3 + h4 , HalftoneImage<short>(2, 2, false));

    bool* data4 = new bool[4] {1, 0, 0, 1 };
    HalftoneImage<bool> h5(2, 2, data4);
    bool* data5 = new bool[4] {0, 1, 1, 0 };
    HalftoneImage<bool> h6(2, 2, data5);
    EXPECT_TRUE(h5 == !h6);

    float* data7 = new float[4] {10, 5, 3, 100 };
    HalftoneImage<float> h7(2, 2, data7);
    HalftoneImage<float> h8 = !h7;
    HalftoneImage<float> h9 = HalftoneImage<float>(2, 2, false);
    EXPECT_EQ(h7 + h8, h9);

    char* data8 = new char[4] {'a', 'b', 'c', 'd' };
    HalftoneImage<char> h10(2, 2, data8);
    HalftoneImage<char> h11 = !h10;
    EXPECT_EQ(h11, HalftoneImage<char>(2, 2, new char[4]{'z', 'y', 'x', 'w'}));
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

    short* data = new short[4] {10, 20, 30, 40 };
    HalftoneImage<short> h2(2, 2, data);
    EXPECT_NEAR(0.0007629, h2.count_fill_factor(), EPSILON);

    short* data2 = new short[4] {10000, 20000, 30000, 15000 };
    HalftoneImage<short> h3(2, 2, data2);
    EXPECT_NEAR(0.572222, h3.count_fill_factor(), EPSILON);

    bool* data3 = new bool[4] {1, 0, 0, 1 };
    HalftoneImage<bool> h4(2, 2, data3);
    EXPECT_NEAR(0.5, h4.count_fill_factor(), EPSILON);

    short* data10 = new short[16] {1,2,3,4,5,6,7,8,9};
    HalftoneImage<short> h10(4, 4, data10);
}

TEST(HalftoneImageTests, InvertValuesAboveLine) {
    short* data1 = new short[4] {10, 5, 3, 100 };
    HalftoneImage<short> h1(2, 2, data1);
    short* data2 = new short[4] {-10, 5, 3, 100 };
    HalftoneImage<short> h2(2, 2, data2);
    invert_values_above_line(h1, Point(5, 5), Point(3, 3));
    EXPECT_EQ(h2, h1);

    
    bool* data3 = new bool[9] {1,1,0,1,0,1,0,0,1};
    HalftoneImage<bool> h3(3, 3, data3);
    bool* data4 = new bool[9] {0,0,1,0,1,1,1,0,1};
    HalftoneImage<bool> h4(3, 3, data4);
    invert_values_above_line(h3, Point(1, 0), Point(3, 2));
    EXPECT_EQ(h4, h3);

    bool* data5 = new bool[9] {1, 1, 0, 1, 0, 1, 0, 0, 1};
    HalftoneImage<bool> h5(3, 3, data5);
    bool* data6 = new bool[9] {0, 0, 1, 1, 1, 0, 0, 0, 0};
    HalftoneImage<bool> h6(3, 3, data6);
    invert_values_above_line(h5, Point(0, 2), Point(2, 0));
    EXPECT_EQ(h6, h5);

    bool* data7 = new bool[9] {1, 1, 0, 1, 0, 1, 0, 0, 1};
    HalftoneImage<bool> h7(3, 3, data7);
    bool* data8 = new bool[9] {0, 0, 0, 0, 0, 1, 0, 0, 1};
    HalftoneImage<bool> h8(3, 3, data8);
    invert_values_above_line(h7, Point(0.75, 0), Point(3, 2.15));
    EXPECT_EQ(h8, h7);
}


