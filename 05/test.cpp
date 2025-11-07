#include "BigInt.h"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(BigIntTest, DefaultTest) {
    BigInt num;
    EXPECT_EQ(num, BigInt(0));
    EXPECT_FALSE(num < BigInt(0));
    EXPECT_FALSE(num > BigInt(0));
}

TEST(BigIntTest, IntStringTest) {
    EXPECT_EQ(BigInt(12345), BigInt("12345"));
    EXPECT_EQ(BigInt(-6789), BigInt("-6789"));
    EXPECT_EQ(BigInt(0), BigInt("0"));
}

TEST(BigIntTest, ExceptionTest) {
    EXPECT_THROW(BigInt("12a34"), std::invalid_argument);
    EXPECT_THROW(BigInt("--123"), std::invalid_argument);
}

TEST(BigIntTest, ArithmeticTest) {
    BigInt a("123456789");
    BigInt b("987654321");
    
    EXPECT_EQ(a + b, BigInt("1111111110"));
    EXPECT_EQ(a + 1, BigInt("123456790"));
    EXPECT_EQ(BigInt(-5) + BigInt(3), BigInt(-2));
    
    EXPECT_EQ(b - a, BigInt("864197532"));
    EXPECT_EQ(a - b, BigInt("-864197532"));
    EXPECT_EQ(a - 1, BigInt("123456788"));
    
    EXPECT_EQ(a * b, BigInt("121932631112635269"));
    EXPECT_EQ(a * 2, BigInt("246913578"));
    EXPECT_EQ(BigInt(-5) * BigInt(3), BigInt(-15));
    
    EXPECT_EQ(-a, BigInt("-123456789"));
    EXPECT_EQ(-BigInt(0), BigInt(0));
}

TEST(BigIntTest, CompareTest) {
    BigInt small("123");
    BigInt medium("456");
    BigInt large("789");
    BigInt negative("-123");
    
    EXPECT_TRUE(small == BigInt("123"));
    EXPECT_FALSE(small == medium);
    
    EXPECT_TRUE(small != medium);
    EXPECT_FALSE(small != BigInt("123"));
    
    EXPECT_TRUE(small < medium);
    EXPECT_TRUE(negative < small);
    EXPECT_FALSE(medium < small);
    
    EXPECT_TRUE(large > medium);
    EXPECT_TRUE(small > negative);
    EXPECT_FALSE(small > large);
    
    EXPECT_TRUE(small <= medium);
    EXPECT_TRUE(small <= BigInt("123"));
    EXPECT_FALSE(large <= medium);
    
    EXPECT_TRUE(large >= medium);
    EXPECT_TRUE(medium >= BigInt("456"));
    EXPECT_FALSE(small >= large);

    EXPECT_TRUE(small == -negative);
}

TEST(BigIntTest, CopyAndMoveTest) {
    BigInt original("123456789");
    
    BigInt copy(original);
    EXPECT_EQ(copy, original);
    
    BigInt assigned;
    assigned = original;
    EXPECT_EQ(assigned, original);
    
    BigInt temp("987654321");
    BigInt moved(std::move(temp));
    EXPECT_EQ(moved, BigInt("987654321"));
    
    BigInt moved_assigned;
    moved_assigned = std::move(moved);
    EXPECT_EQ(moved_assigned, BigInt("987654321"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}