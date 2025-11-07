#ifndef BIGINT_H
#define BIGINT_H

#include <cstdint>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <compare>

class BigInt {
public:
    BigInt();
    BigInt(int32_t val);
    BigInt(const std::string& str);
    BigInt(const BigInt& other);
    BigInt(BigInt&& other) noexcept;

    ~BigInt();

    BigInt& operator=(const BigInt& other);
    BigInt& operator=(BigInt&& other) noexcept;

    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;
    BigInt operator-() const;

    BigInt operator+(int32_t other) const;
    BigInt operator-(int32_t other) const;
    BigInt operator*(int32_t other) const;

    std::strong_ordering operator<=>(const BigInt& other) const;
    bool operator==(const BigInt& other) const;

    friend std::ostream& operator<<(std::ostream& os, const BigInt& num);

private:
    void resize(size_t new_size);
    void remove_zeroes();
    int compare_abs(const BigInt& other) const;
    void add_abs(const BigInt& other);
    void subtract_abs(const BigInt& other);

private:
    char* digits;
    size_t size;
    bool sign;
};

#endif
