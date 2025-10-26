#include "matrix.h"

Matrix::ProxyRow::ProxyRow(int32_t *data, size_t cols)
    : _data(data), _cols(cols) {}


Matrix::ProxyRow::ProxyRow(const ProxyRow& other)
    : _data(nullptr), _cols(other._cols) {
    if (_cols > 0) {
        _data = new int32_t[_cols];
        for (size_t i = 0; i < _cols; ++i)
            _data[i] = other._data[i];
    }
}

Matrix::ProxyRow::ProxyRow(ProxyRow&& other) noexcept
    : _data(other._data), _cols(other._cols) {
    other._cols = 0;
    other._data = nullptr;
}

Matrix::ProxyRow& Matrix::ProxyRow::operator=(const ProxyRow& other) {
    if (this != &other) {
        delete[] _data;
        _cols = other._cols;
        if (_cols > 0) {
            _data = new int32_t[_cols];
            for (size_t i = 0; i < _cols; ++i)
                _data[i] = other._data[i];
        } else 
            _data = nullptr;
    }
    return *this;
}

Matrix::ProxyRow& Matrix::ProxyRow::operator=(ProxyRow&& other) noexcept {
    if (this != &other) {
        delete[] _data;
        _data = other._data;
        _cols = other._cols;
        other._data = nullptr;
        other._cols = 0;
    }
    return *this;
}

Matrix::ProxyRow::~ProxyRow() {
    delete[] _data;
}

size_t Matrix::ProxyRow::getCols() const {
    return _cols;
}

int32_t& Matrix::ProxyRow::operator[](size_t j) {
    if (j >= _cols) throw std::out_of_range("Column index out of range");
    return _data[j];
}

const int32_t& Matrix::ProxyRow::operator[](size_t j) const {
    if (j >= _cols) throw std::out_of_range("Column index out of range");
    return _data[j];
}

void Matrix::clean() noexcept {
    if (_rows) {
        for (size_t i = 0; i < _n; ++i)
            delete _rows[i];
        delete[] _rows;
        _rows = nullptr;
    }
    _n = 0;
    _m = 0;
}

void Matrix::copyFrom(const Matrix& other) {
    _n = other._n;
    _m = other._m;
    if (_n > 0 && _m > 0) {
        _rows = new ProxyRow*[_n];
        size_t i = 0;
        try {
            for (; i < _n; ++i)
                _rows[i] = new ProxyRow(*other._rows[i]);
        } catch (...) {
            for (size_t k = 0; k < i; ++k) 
                delete _rows[k];
            delete[] _rows;
        }
    } else 
        _rows = nullptr;
}

Matrix::Matrix(size_t n, size_t m) 
    : _rows(nullptr), _n(n), _m(m) {
    if (n > 0 && m > 0) {
        _rows = new ProxyRow*[_n];
        size_t i = 0;
        try {
            for (; i < _n; ++i) {
                _rows[i] = new ProxyRow(new int32_t[_m], _m);
                for (size_t j = 0; j < _m; ++j)
                    (*_rows[i])[j] = 0;
            }
        } catch (...) {
            for (size_t k = 0; k < i; ++k) 
                delete _rows[k];
            delete[] _rows;
        }
    }
}

Matrix::Matrix(const Matrix& other)
    : _rows(nullptr), _n(other._n), _m(other._m) {
    copyFrom(other);
}

Matrix::Matrix(Matrix&& other) noexcept 
    : _rows(other._rows), _n(other._n), _m(other._m) {
    other._rows = nullptr;
    other._n = 0;
    other._m = 0;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        clean();
        copyFrom(other);
    }
    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        clean();
        _rows = other._rows;
        _n = other._n;
        _m = other._m;
        other._rows = nullptr;
        other._n = 0;
        other._m = 0;
    }
    return *this;
}

Matrix::~Matrix() {
    clean();
}

size_t Matrix::getRows() const {
    return _n;
}

size_t Matrix::getCols() const {
    return _m;
}

Matrix::ProxyRow& Matrix::operator[](size_t i) {
    if (i >= _n) throw std::out_of_range("Row index out of range");
    return *_rows[i];
}

const Matrix::ProxyRow& Matrix::operator[](size_t i) const {
    if (i >= _n) throw std::out_of_range("Row index out of range");
    return *_rows[i];
}

Matrix& Matrix::operator*=(int32_t k) {
    for (size_t i = 0; i < _n; ++i) 
        for (size_t j = 0; j < _m; ++j) 
            (*_rows[i])[j] *= k;
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (_n != other._n || _m != other._m) throw std::invalid_argument("Different dimensions");
    
    Matrix res(_n, _m);
    for (size_t i = 0; i < _n; ++i) 
        for (size_t j = 0; j < _m; ++j) 
            res[i][j] = (*this)[i][j] + other[i][j];
    return res;
}

bool Matrix::operator==(const Matrix& other) const {
    if (_n != other._n || _m != other._m) return false;

    for (size_t i = 0; i < _n; ++i)
        for (size_t j = 0; j < _m; ++j)
            if ((*this)[i][j] != other[i][j])
                return false;
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (size_t i = 0; i < matrix._n; ++i) {
        for (size_t j = 0; j < matrix._m; ++j) {
            os << matrix[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}
