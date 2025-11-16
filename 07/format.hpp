#include "format.h" 

template<Streamable... Args>
std::string format(const std::string& fmt, Args&&... args) {
    std::vector<std::string> arguments;
    std::ostringstream oss;
    
    auto store_args = [&oss, &arguments](auto&& arg) {
        oss.str("");
        oss << std::forward<decltype(arg)>(arg);
        arguments.push_back(oss.str());
    };
    
    (store_args(std::forward<Args>(args)), ...);
    std::string result;
    size_t i = 0;
    size_t n = fmt.size();
    while (i < n) {
        if (fmt[i] == '{') {
            size_t j = i + 1;
            while (j < n && fmt[j] != '}') {
                if (fmt[j] == '{') throw FormatError("Nested curly braces are not allowed");
                ++j;
            }
            if (j == n) throw FormatError("Unclosed curly brace");
            std::string number_str = fmt.substr(i + 1, j - i - 1);
            if (number_str.empty()) throw FormatError("Empty curly braces");
            for (char c : number_str)
                if (!std::isdigit(static_cast<unsigned char>(c))) 
                    throw FormatError("Non-digit character in argument index: " + number_str);
          
            size_t index;
            try {
                index = std::stoul(number_str);
            } catch (const std::exception&) {
                throw FormatError("Invalid argument index: " + number_str);
            }
            
            if (index >= arguments.size()) throw FormatError("Argument index out of range: " + std::to_string(index));
            result += arguments[index];
            i = j + 1; 
        } 
        else if (fmt[i] == '}') throw FormatError("Unopened curly brace");
        else result += fmt[i++];
    }
    return result;
}
