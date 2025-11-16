#include "format.h"
#include <gtest/gtest.h>
#include <string>

TEST(FormatTest, BasicFormatting) {
    EXPECT_EQ(format("{0} + {1} = {2}", 2, 3, 5), "2 + 3 = 5");
    EXPECT_EQ(format("{1} + {1} = {0}", 2, "one"), "one + one = 2");
    EXPECT_EQ(format("{0}{1}{0}", "a", "b"), "aba");
}

TEST(FormatTest, RepeatingArguments) {
    EXPECT_EQ(format("{0}{0}{0}", "x"), "xxx");
    EXPECT_EQ(format("{2}{1}{0}", "a", "b", "c"), "cba");
}

TEST(FormatTest, DifferentTypes) {
    EXPECT_EQ(format("{0} {1} {2}", 42, 3.14, "hello"), "42 3.14 hello");
    EXPECT_EQ(format("{0}", true), "1");
    EXPECT_EQ(format("{0}", false), "0");
}

TEST(FormatTest, EmptyString) {
    EXPECT_EQ(format(""), "");
    EXPECT_EQ(format("{0}", ""), "");
}

TEST(FormatTest, NoPlaceholders) {
    EXPECT_EQ(format("Hello, World!"), "Hello, World!");
    EXPECT_EQ(format("Simple text"), "Simple text");
}

TEST(FormatTest, ComplexExample) {
    std::string result = format("Name: {0}, Age: {1}, Score: {2}", "Alice", 25, 95.5);
    EXPECT_EQ(result, "Name: Alice, Age: 25, Score: 95.5");
}

TEST(FormatTest, Exceptions) {
    EXPECT_THROW(format("{0} {1}", 1), FormatError);
    EXPECT_THROW(format("{5}", 1), FormatError);
    
    EXPECT_THROW(format("{0", 1), FormatError);
    EXPECT_THROW(format("0}", 1), FormatError);
    EXPECT_THROW(format("{}", 1), FormatError);
    EXPECT_THROW(format("{0}{", 1), FormatError);
    
    EXPECT_THROW(format("{{0}}", 1), FormatError);
    
    EXPECT_THROW(format("{a}", 1), FormatError);
    EXPECT_THROW(format("{0a}", 1), FormatError);
    EXPECT_THROW(format("{ }", 1), FormatError);
}

TEST(FormatTest, LargeNumbers) {
    EXPECT_EQ(format("{0}", 1234567890), "1234567890");
    EXPECT_EQ(format("{0}", 3.1415926535), "3.14159");
}

TEST(FormatTest, SpecialCharacters) {
    EXPECT_EQ(format("{0}", "line1\nline2"), "line1\nline2");
    EXPECT_EQ(format("{0}", "tab\tcharacter"), "tab\tcharacter");
}

struct Point {
    int x, y;
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

TEST(FormatTest, CustomType) {
    Point p{10, 20};
    EXPECT_EQ(format("Point: {0}", p), "Point: (10,20)");
}

TEST(FormatTest, MixedContent) {
    auto result = format("Text {0} more {1} end", "middle", "text");
    EXPECT_EQ(result, "Text middle more text end");
}

TEST(FormatTest, MultipleSpaces) {
    EXPECT_EQ(format("{0}  {1}   {2}", "a", "b", "c"), "a  b   c");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}