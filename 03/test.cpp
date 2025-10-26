#include "token_parser.h" 
#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>

class TokenParserTest : public ::testing::Test {
protected:
    void SetUp() override {
        digit_tokens.clear();
        string_tokens.clear();
        
        parser.SetDigitTokenCallback([this](uint64_t num) {
            digit_tokens.push_back(num);
        });
        
        parser.SetStringTokenCallback([this](const std::string& str) {
            string_tokens.push_back(str);
        });
    }

    TokenParser parser;
    std::vector<uint64_t> digit_tokens;
    std::vector<std::string> string_tokens;
};

TEST_F(TokenParserTest, EmptyString) {
    parser.Parse("");
    EXPECT_TRUE(digit_tokens.empty());
    EXPECT_TRUE(string_tokens.empty());
}

TEST_F(TokenParserTest, OnlySpaces) {
    parser.Parse("   \t\n  \r ");
    EXPECT_TRUE(digit_tokens.empty());
    EXPECT_TRUE(string_tokens.empty());
}

TEST_F(TokenParserTest, SingleDigitToken) {
    parser.Parse("123");
    EXPECT_EQ(digit_tokens.size(), 1);
    EXPECT_EQ(string_tokens.size(), 0);
    EXPECT_EQ(digit_tokens[0], 123);
}

TEST_F(TokenParserTest, SingleStringToken) {
    parser.Parse("hello");
    EXPECT_EQ(digit_tokens.size(), 0);
    EXPECT_EQ(string_tokens.size(), 1);
    EXPECT_EQ(string_tokens[0], "hello");
}

TEST_F(TokenParserTest, MultipleDigitTokens) {
    parser.Parse("123 456 789");
    EXPECT_EQ(digit_tokens.size(), 3);
    EXPECT_EQ(string_tokens.size(), 0);
    EXPECT_EQ(digit_tokens[0], 123);
    EXPECT_EQ(digit_tokens[1], 456);
    EXPECT_EQ(digit_tokens[2], 789);
}

TEST_F(TokenParserTest, MultipleStringTokens) {
    parser.Parse("hello world test");
    EXPECT_EQ(digit_tokens.size(), 0);
    EXPECT_EQ(string_tokens.size(), 3);
    EXPECT_EQ(string_tokens[0], "hello");
    EXPECT_EQ(string_tokens[1], "world");
    EXPECT_EQ(string_tokens[2], "test");
}

TEST_F(TokenParserTest, MixedTokens) {
    parser.Parse("hello 123 world 456 test");
    EXPECT_EQ(digit_tokens.size(), 2);
    EXPECT_EQ(string_tokens.size(), 3);
    EXPECT_EQ(digit_tokens[0], 123);
    EXPECT_EQ(digit_tokens[1], 456);
    EXPECT_EQ(string_tokens[0], "hello");
    EXPECT_EQ(string_tokens[1], "world");
    EXPECT_EQ(string_tokens[2], "test");
}

TEST_F(TokenParserTest, TokensWithVariousSpaces) {
    parser.Parse("  hello   123  \tworld\n456\r\ntest  ");
    EXPECT_EQ(digit_tokens.size(), 2);
    EXPECT_EQ(string_tokens.size(), 3);
    EXPECT_EQ(digit_tokens[0], 123);
    EXPECT_EQ(digit_tokens[1], 456);
    EXPECT_EQ(string_tokens[0], "hello");
    EXPECT_EQ(string_tokens[1], "world");
    EXPECT_EQ(string_tokens[2], "test");
}

TEST_F(TokenParserTest, LargeNumbers) {
    parser.Parse("18446744073709551615 9999999999999999999");
    EXPECT_EQ(digit_tokens.size(), 2);
    EXPECT_EQ(digit_tokens[0], 18446744073709551615ULL);
    EXPECT_EQ(digit_tokens[1], 9999999999999999999ULL);
}

TEST_F(TokenParserTest, VeryLargeNumberBecomesString) {
    parser.Parse("999999999999999999999999999999");
    EXPECT_EQ(digit_tokens.size(), 0);
    EXPECT_EQ(string_tokens.size(), 1);
    EXPECT_EQ(string_tokens[0], "999999999999999999999999999999");
}

TEST_F(TokenParserTest, AlphanumericTokens) {
    parser.Parse("abc123 123abc test123test");
    EXPECT_EQ(digit_tokens.size(), 0);
    EXPECT_EQ(string_tokens.size(), 3);
    EXPECT_EQ(string_tokens[0], "abc123");
    EXPECT_EQ(string_tokens[1], "123abc");
    EXPECT_EQ(string_tokens[2], "test123test");
}

TEST_F(TokenParserTest, SpecialCharacters) {
    parser.Parse("hello! @world# test$%^");
    EXPECT_EQ(digit_tokens.size(), 0);
    EXPECT_EQ(string_tokens.size(), 3);
    EXPECT_EQ(string_tokens[0], "hello!");
    EXPECT_EQ(string_tokens[1], "@world#");
    EXPECT_EQ(string_tokens[2], "test$%^");
}

TEST_F(TokenParserTest, NoCallbacksSet) {
    TokenParser local_parser;

    EXPECT_NO_THROW(local_parser.Parse("hello 123 world"));
}

TEST_F(TokenParserTest, OnlyDigitCallback) {
    TokenParser local_parser;
    std::vector<uint64_t> local_digits;
    
    local_parser.SetDigitTokenCallback([&local_digits](uint64_t num) {
        local_digits.push_back(num);
    });
    
    local_parser.Parse("hello 123 world 456");
    
    EXPECT_EQ(local_digits.size(), 2);
    EXPECT_EQ(local_digits[0], 123);
    EXPECT_EQ(local_digits[1], 456);
}

TEST_F(TokenParserTest, OnlyStringCallback) {
    TokenParser local_parser;
    std::vector<std::string> local_strings;
    
    local_parser.SetStringTokenCallback([&local_strings](const std::string& str) {
        local_strings.push_back(str);
    });
    
    local_parser.Parse("hello 123 world 456");
    
    EXPECT_EQ(local_strings.size(), 4);
    EXPECT_EQ(local_strings[0], "hello");
    EXPECT_EQ(local_strings[1], "123");
    EXPECT_EQ(local_strings[2], "world");
    EXPECT_EQ(local_strings[3], "456");
}

TEST_F(TokenParserTest, CallbackOrder) {
    std::vector<std::string> callback_order;
    
    TokenParser local_parser;
    local_parser.SetDigitTokenCallback([&callback_order](uint64_t num) {
        callback_order.push_back("digit:" + std::to_string(num));
    });
    local_parser.SetStringTokenCallback([&callback_order](const std::string& str) {
        callback_order.push_back("string:" + str);
    });
    
    local_parser.Parse("first 123 second 456 third");
    
    EXPECT_EQ(callback_order.size(), 5);
    EXPECT_EQ(callback_order[0], "string:first");
    EXPECT_EQ(callback_order[1], "digit:123");
    EXPECT_EQ(callback_order[2], "string:second");
    EXPECT_EQ(callback_order[3], "digit:456");
    EXPECT_EQ(callback_order[4], "string:third");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}