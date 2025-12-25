#include "header.h"
#include <iostream>

void Print(const Matrix& m)
{
    for (std::size_t i = 0; i < m.m_; ++i) {
        for (std::size_t j = 0; j < m.n_; ++j)
            std::cout << m.data_[i * m.n_ + j] << ' ';
        std::cout << '\n';
    }
}

int main()
{
    Matrix a, b;
    Construct(a, 3, 2); // 3*2
    Construct(b, 3, 2);

    // заполним матрицы
    for (std::size_t i = 0; i < a.m_; ++i)
        for (std::size_t j = 0; j < a.n_; ++j) {
            a.data_[i * a.n_ + j] = static_cast<int>(i + j);
            b.data_[i * b.n_ + j] = static_cast<int>(1);
        }

    std::cout << "A:\n"; Print(a);
    std::cout << "B:\n"; Print(b);

    Matrix sum = Add(a, b);
    std::cout << "A + B:\n"; Print(sum);

    Matrix diff = Sub(a, b);
    std::cout << "A - B:\n"; Print(diff);

    Matrix c, d;
    Construct(c, 2, 3); // 2x3
    Construct(d, 3, 2); // 3x2
    for (std::size_t i = 0; i < c.m_; ++i)
        for (std::size_t j = 0; j < c.n_; ++j)
            c.data_[i * c.n_ + j] = 1;
    for (std::size_t i = 0; i < d.m_; ++i)
        for (std::size_t j = 0; j < d.n_; ++j)
            d.data_[i * d.n_ + j] = 2;

    Matrix prod = Mult(c, d);
    std::cout << "C * D:\n"; Print(prod);

    Transposition(prod);
    std::cout << "Transpose(C * D):\n"; Print(prod);

    Destruct(a);
    Destruct(b);
    Destruct(sum);
    Destruct(diff);
    Destruct(c);
    Destruct(d);
    Destruct(prod);

    return 0;
}
