#define _CRT_SECURE_NO_WARNINGS
#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include "digit_processor.h"

namespace {
    const int CAP = 64;

    std::string run(const char* input) {
        char buf[CAP];
        std::strcpy(buf, input);
        EXPECT_TRUE(process_digits(buf, CAP));
        return std::string(buf);
    }
}

TEST(DigitProcessor, EmptyString) {
    EXPECT_EQ(run(""), "");
}

TEST(DigitProcessor, NoDigits) {
    EXPECT_EQ(run("abc"), "abc");
}

TEST(DigitProcessor, AllOdd) {
    EXPECT_EQ(run("13579"), "");
}

TEST(DigitProcessor, AllEven) {
    EXPECT_EQ(run("2468"), "2++4++6++8");
}

TEST(DigitProcessor, EvenDigitAtEnd) {
    EXPECT_EQ(run("x8"), "x8");
}

TEST(DigitProcessor, EvenDigitNotAtEnd) {
    EXPECT_EQ(run("x2y"), "x2++y");
}

TEST(DigitProcessor, SingleOddDigit) {
    EXPECT_EQ(run("7"), "");
}

TEST(DigitProcessor, FullExample) {
    EXPECT_EQ(run("a1b2c3d4 55 x8"), "ab2++cd4++  x8");
}

TEST(DigitProcessor, NotEnoughSpace) {
    char buf[6];
    std::strcpy(buf, "2468");
    EXPECT_FALSE(process_digits(buf, 6));
}