#include "BigInt.h"

void BigInt::resize(size_t new_size) {
    if (new_size == size) return;
    char* new_digits = new char[new_size]();
    if (new_digits) {
        if (digits) {
            size_t copy_size = std::min(size, new_size);
            std::memcpy(new_digits, digits, copy_size);
            delete[] digits;
        }
        
        digits = new_digits;
        size = new_size;
    }
}

void BigInt::remove_zeroes() {
    size_t new_size = size;
    while (new_size > 1 && digits[new_size - 1] == 0) --new_size;
    if (new_size != size) resize(new_size);
    if (size == 1 && digits[0] == 0) sign = false;
}

int BigInt::compare_abs(const BigInt& other) const {
    if (size != other.size) return size > other.size ? 1 : -1;
    for (int i = size - 1; i >= 0; --i) {
        if (digits[i] != other.digits[i])
            return digits[i] > other.digits[i] ? 1 : -1;
    }
    return 0;
}

void BigInt::add_abs(const BigInt& other) {
    size_t max_size = std::max(size, other.size) + 1;
    resize(max_size);
    int carry = 0;
    for (size_t i = 0; i < max_size; ++i) {
        int sum = carry;
        if (i < size) sum += digits[i];
        if (i < other.size) sum += other.digits[i];
        
        digits[i] = sum % 10;
        carry = sum / 10;
    }
    remove_zeroes();
}

void BigInt::subtract_abs(const BigInt& other) {
    int borrow = 0;
    for (size_t i = 0; i < size; ++i) {
        int diff = digits[i] - borrow;
        if (i < other.size) diff -= other.digits[i];
        if (diff < 0) {
            borrow = 1;
            diff += 10;
        } else borrow = 0;
        digits[i] = diff;
    }
    remove_zeroes();
}

BigInt::BigInt() : digits(nullptr), size(0), sign(false) {
    resize(1);
    digits[0] = 0;
}

BigInt::BigInt(int32_t val) : digits(nullptr), size(0), sign(val < 0) {
    uint32_t abs_val = std::abs(static_cast<int64_t>(val));
    if (abs_val == 0) {
        resize(1);
        digits[0] = 0;
        sign = false;
        return;
    }

    uint32_t temp = abs_val;
    size_t count = 0;
    while (temp > 0) {
        temp /= 10;
        ++count;
    }
    resize(count);
    
    temp = abs_val;
    for (size_t i = 0; i < size; ++i) {
        digits[i] = temp % 10;
        temp /= 10;
    }
}

BigInt::BigInt(const std::string& str) : digits(nullptr), size(0), sign(false) {
    if (str.empty()) {
        resize(1);
        digits[0] = 0;
        return;
    }
    size_t start = 0;
    if (str[0] == '-') {
        sign = true;
        start = 1;
    } else if (str[0] == '+') start = 1;

    while (start < str.length() && str[start] == '0') ++start;

    if (start == str.length()) {
        resize(1);
        digits[0] = 0;
        sign = false;
        return;
    }

    size_t num_digits = str.length() - start;
    resize(num_digits);
    for (size_t i = 0; i < size; i++) {
        char c = str[str.length() - 1 - i];
        if (c < '0' || c > '9') {
            throw std::invalid_argument("Invalid char");
        }
        digits[i] = c - '0';
    }
    remove_zeroes();
}

BigInt::BigInt(const BigInt& other) : digits(nullptr), size(0), sign(other.sign) {
    resize(other.size);
    std::memcpy(digits, other.digits, size);
}

BigInt::BigInt(BigInt&& other) noexcept : digits(other.digits), size(other.size), sign(other.sign) {
    other.digits = nullptr;
    other.size = 0;
    other.sign = false;
}

BigInt::~BigInt() {
    delete[] digits;
}

BigInt& BigInt::operator=(const BigInt& other) {
    if (this != &other) {
        resize(other.size);
        std::memcpy(digits, other.digits, size);
        sign = other.sign;
    }
    return *this;
}

BigInt& BigInt::operator=(BigInt&& other) noexcept {
    if (this != &other) {
        delete[] digits;
        
        digits = other.digits;
        size = other.size;
        sign = other.sign;
        
        other.digits = nullptr;
        other.size = 0;
        other.sign = false;
    }
    return *this;
}

BigInt BigInt::operator+(const BigInt& other) const {
    if (sign == other.sign) {
        BigInt result = *this;
        result.add_abs(other);
        result.sign = sign;
        return result;
    } else {
        int cmp = compare_abs(other);
        if (cmp == 0) {
            return BigInt(0);
        }
        
        BigInt result;
        if (cmp > 0) {
            result = *this;
            result.subtract_abs(other);
            result.sign = sign;
        } else {
            result = other;
            result.subtract_abs(*this);
            result.sign = other.sign;
        }
        return result;
    }
}

BigInt BigInt::operator-(const BigInt& other) const {
    return *this + (-other);
}

BigInt BigInt::operator*(const BigInt& other) const {
    if (*this == BigInt(0) || other == BigInt(0)) return BigInt(0);
    
    BigInt result;
    result.resize(size + other.size);
    for (size_t i = 0; i < size; ++i) {
        int carry = 0;
        for (size_t j = 0; j < other.size || carry; ++j) {
            long long product = result.digits[i + j] + digits[i] * (j < other.size ? other.digits[j] : 0) + carry;
            result.digits[i + j] = product % 10;
            carry = product / 10;
        }
    }
    
    result.sign = sign != other.sign;
    result.remove_zeroes();
    return result;
}

BigInt BigInt::operator-() const {
    BigInt result = *this;
    if (result != BigInt(0))
        result.sign = !result.sign;
    return result;
}

BigInt BigInt::operator+(int32_t other) const {
    return *this + BigInt(other);
}

BigInt BigInt::operator-(int32_t other) const {
    return *this - BigInt(other);
}

BigInt BigInt::operator*(int32_t other) const {
    return *this * BigInt(other);
}

std::strong_ordering BigInt::operator<=>(const BigInt& other) const {
    if (sign != other.sign)
        return sign ? std::strong_ordering::less : std::strong_ordering::greater;
    int cmp = compare_abs(other);
    if (cmp == 0) return std::strong_ordering::equal;
    if (sign) return cmp > 0 ? std::strong_ordering::less : std::strong_ordering::greater;
    else return cmp > 0 ? std::strong_ordering::greater : std::strong_ordering::less;
}

bool BigInt::operator==(const BigInt& other) const {
    if (sign != other.sign || size != other.size) return false;
    for (size_t i = 0; i < size; ++i)
        if (digits[i] != other.digits[i])
            return false;
    return true;
}

std::ostream& operator<<(std::ostream& os, const BigInt& num) {
    if (num.sign && !(num.size == 1 && num.digits[0] == 0)) os << '-';
    
    for (size_t i = num.size; i > 0; --i)
        os << static_cast<char>(num.digits[i - 1] + '0');
    
    return os;
}