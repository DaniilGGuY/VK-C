#ifndef MATRIX_H
#define MATRIX_H

#include <cstdint>
#include <cstddef>
#include <iostream>
#include <stdexcept>

class Matrix {
private:
    class ProxyRow {
        int32_t* _data;
        size_t _cols;
    public:
        ProxyRow(int32_t *data = nullptr, size_t cols = 0);

        ProxyRow(const ProxyRow& other);
        ProxyRow(ProxyRow&& other) noexcept;

        ProxyRow& operator=(const ProxyRow& other);
        ProxyRow& operator=(ProxyRow&& other) noexcept;

        ~ProxyRow();

        size_t getCols() const;

        int32_t& operator[](size_t j);
        const int32_t& operator[](size_t j) const;
    };
public:
    Matrix(size_t n = 0, size_t m = 0);

    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;

    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;

    ~Matrix();

    size_t getRows() const;
    size_t getCols() const;

    ProxyRow& operator[](size_t i);
    const ProxyRow& operator[](size_t i) const;

    Matrix& operator*=(int32_t k);
    Matrix operator+(const Matrix& other) const;

    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

private:
    void clean() noexcept;
    void copyFrom(const Matrix& other);

    ProxyRow **_rows;
    size_t _n;
    size_t _m;
};

#endif
