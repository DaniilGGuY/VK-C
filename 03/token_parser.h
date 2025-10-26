#ifndef TOKEN_PARSER_H
#define TOKEN_PARSER_H

#include <iostream>
#include <functional>
#include <string>
#include <cctype>
#include <cstdint>
#include <sstream>

class TokenParser
{
    using func_digit_ptr = std::function<void(uint64_t)>;
    using func_str_ptr = std::function<void(const std::string&)>;

public:
    TokenParser() = default;

    void SetDigitTokenCallback(func_digit_ptr callback);

    void SetStringTokenCallback(func_str_ptr callback);

    void Parse(const std::string &text);

private:
    void ProcessToken(const std::string& token);

    func_digit_ptr _digit_callback = nullptr;
    func_str_ptr _string_callback = nullptr;
};

#endif