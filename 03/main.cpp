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

    void SetDigitTokenCallback(func_digit_ptr callback) { _digit_callback = callback; }

    void SetStringTokenCallback(func_str_ptr callback) { _string_callback = callback; }

    void Parse(const std::string &text) {
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

private:
    void ProcessToken(const std::string& token) {
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
                if (_digit_callback) { _digit_callback(number); }
                return;
            } catch (const std::out_of_range&) {
            } catch (const std::invalid_argument&) {
            }
        }
        if (_string_callback) { _string_callback(token); }
    }

    func_digit_ptr _digit_callback = nullptr;
    func_str_ptr _string_callback = nullptr;
};

int main()
{
    TokenParser parser;
    
    parser.SetDigitTokenCallback([](uint64_t num) {
        std::cout << "Found number: " << num << std::endl;
    });
    
    parser.SetStringTokenCallback([](const std::string& str) {
        std::cout << "Found string: \"" << str << "\"" << std::endl;
    });

    std::string line;
    while (std::getline(std::cin, line)) {
        parser.Parse(line);
    }

    return 0;
}