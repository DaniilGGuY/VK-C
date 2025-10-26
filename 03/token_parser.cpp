#include "token_parser.h"

void TokenParser::SetDigitTokenCallback(func_digit_ptr callback) { 
    _digit_callback = callback; 
}

void TokenParser::SetStringTokenCallback(func_str_ptr callback) { 
    _string_callback = callback; 
}

void TokenParser::Parse(const std::string &text) {
    size_t i = 0, n = text.length();
    while (i < n) {
        while (i < n && std::isspace(text[i])) { ++i; }
        if (i >= n) { break; }
        size_t start = i;
        while (i < n && !std::isspace(text[i])) { ++i; }
        size_t end = i;
        std::string token = text.substr(start, end - start);
        ProcessToken(token);
    }
}

void TokenParser::ProcessToken(const std::string& token) {
    bool is_digit = !token.empty();
    for (char c : token) {
        if (!std::isdigit(c)) {
            is_digit = false;
            break;
        }
    }
    if (is_digit) {
        try {
            uint64_t number = std::stoull(token);
            if (_digit_callback) { 
                _digit_callback(number);
                return;
            }
        } catch (const std::out_of_range&) {
        } catch (const std::invalid_argument&) {
        }
    }
    if (_string_callback) { _string_callback(token); }
}