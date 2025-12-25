#ifndef LAB7_8_9_HEADER_H
#define LAB7_8_9_HEADER_H

#include <cstring>
#include <cstddef>
#include <algorithm>

//задание 1
static std::size_t MyStrLen(const char* s)
{
    std::size_t len = 0;
    while (s && s[len] != '\0')
        ++len;
    return len;
}

char* CopyString(const char* str)
{
    if (!str)
        return nullptr;

    std::size_t len = MyStrLen(str);
    char* result = new char[len + 1];

    std::memcpy(result, str, len);   // без str* функций
    result[len] = '\0';

    return result;
}

char* ConcatenateStrings(const char* a, const char* b)
{
    if (!a && !b)
        return nullptr;

    if (!a) return CopyString(b);
    if (!b) return CopyString(a);

    std::size_t lenA = MyStrLen(a);
    std::size_t lenB = MyStrLen(b);

    char* result = new char[lenA + lenB + 1];

    std::memcpy(result,       a, lenA);
    std::memcpy(result+lenA,  b, lenB);
    result[lenA + lenB] = '\0';

    return result;
}

//задание 2
struct Matrix {
    // двумерный массив с данными (n * m элементов)
    int* data_ = nullptr;
    // количество столбцов
    std::size_t n_ = 0;
    // количество строк
    std::size_t m_ = 0;
};

static std::size_t Index(std::size_t row, std::size_t col,
                         std::size_t cols)
{
    return row * cols + col;
}

void Construct(Matrix& out, std::size_t n, std::size_t m)
{
    if (n == 0 || m == 0) {
        out.data_ = nullptr;
        out.n_ = out.m_ = 0;
        return;
    }

    out.n_ = n;
    out.m_ = m;
    out.data_ = new int[n * m]{0};  // заполнить нулями
}

void Destruct(Matrix& in)
{
    delete[] in.data_;
    in.data_ = nullptr;
    in.n_ = in.m_ = 0;
}

Matrix Copy(const Matrix& matrix)
{
    Matrix res;
    if (!matrix.data_ || matrix.n_ == 0 || matrix.m_ == 0)
        return res;

    Construct(res, matrix.n_, matrix.m_);
    std::copy(matrix.data_, matrix.data_ + matrix.n_ * matrix.m_,
              res.data_);
    return res;
}

Matrix Add(const Matrix& a, const Matrix& b)
{
    Matrix res;
    if (a.n_ == 0 || a.m_ == 0 || b.n_ == 0 || b.m_ == 0)
        return res;
    if (a.n_ != b.n_ || a.m_ != b.m_)
        return res;

    Construct(res, a.n_, a.m_);
    std::size_t total = a.n_ * a.m_;
    for (std::size_t i = 0; i < total; ++i)
        res.data_[i] = a.data_[i] + b.data_[i];

    return res;
}

Matrix Sub(const Matrix& a, const Matrix& b)
{
    Matrix res;
    if (a.n_ == 0 || a.m_ == 0 || b.n_ == 0 || b.m_ == 0)
        return res;
    if (a.n_ != b.n_ || a.m_ != b.m_)
        return res;

    Construct(res, a.n_, a.m_);
    std::size_t total = a.n_ * a.m_;
    for (std::size_t i = 0; i < total; ++i)
        res.data_[i] = a.data_[i] - b.data_[i];

    return res;
}

Matrix Mult(const Matrix& a, const Matrix& b)
{
    Matrix res;
    if (a.n_ == 0 || a.m_ == 0 || b.n_ == 0 || b.m_ == 0)
        return res;
    // a: m_a x n_a, b: m_b x n_b, но по условию n_ — столбцы, m_ — строки
    if (a.n_ != b.m_)             // число столбцов A = числу строк B
        return res;

    // результат: матрица размером a.m_ x b.n_
    Construct(res, b.n_, a.m_);   // n_ = столбцы, m_ = строки

    for (std::size_t i = 0; i < a.m_; ++i)          // по строкам A
        for (std::size_t j = 0; j < b.n_; ++j) {    // по столбцам B
            int sum = 0;
            for (std::size_t k = 0; k < a.n_; ++k) {
                int valA = a.data_[Index(i, k, a.n_)];
                int valB = b.data_[Index(k, j, b.n_)];
                sum += valA * valB;
            }
            res.data_[Index(i, j, res.n_)] = sum;
        }

    return res;
}

void Transposition(Matrix& matrix)
{
    if (matrix.n_ == 0 || matrix.m_ == 0 || !matrix.data_)
        return;

    Matrix tmp;
    Construct(tmp, matrix.m_, matrix.n_); // поменять размеры местами

    for (std::size_t i = 0; i < matrix.m_; ++i)
        for (std::size_t j = 0; j < matrix.n_; ++j)
            tmp.data_[Index(j, i, tmp.n_)] =
                matrix.data_[Index(i, j, matrix.n_)];

    Destruct(matrix);
    matrix = tmp;                // копирование полей (уже своя память)
}

bool operator==(const Matrix& a, const Matrix& b)
{
    if (a.n_ != b.n_ || a.m_ != b.m_)
        return false;
    std::size_t total = a.n_ * a.m_;
    for (std::size_t i = 0; i < total; ++i)
        if (a.data_[i] != b.data_[i])
            return false;
    return true;
}






#endif //LAB7_8_9_HEADER_H