#ifndef FORMAT_H
#define FORMAT_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <type_traits>

class FormatError : public std::runtime_error {
public:
    explicit FormatError(const std::string& message) : std::runtime_error(message) {}
};

template<typename T>
concept Streamable = requires(std::ostream& os, T&& t) {
    os << std::forward<T>(t);
};

template<Streamable... Args>
std::string format(const std::string& fmt, Args&&... args);

#include "format.hpp"  

#endif