#include <iostream>
#include <vector>

#ifndef __MATRIX_H
#define __MATRIX_H

template <class T>
class Matrix
{
public:
    typedef std::vector<std::vector<T>> datatype;

    int n;
    int m;
    datatype data;

    Matrix() = default;
    
    Matrix(const datatype &s) : data(s)
    {
        n = s.size();
        m = s[0].size();
    }

    static Matrix<T> zero_matrix(int n, int m)
    {
        datatype vec;
        vec.resize(n);
        for (int i = 0; i < n; i++)
        {
            vec[i].resize(m);
        }
        return Matrix<T>(vec);
    }

    Matrix<T> operator+(const Matrix<T> &mat) const
    {
        int na = mat.n;
        int ma = mat.m;
        auto sum = zero_matrix(na, ma);
        for (int i = 0; i < na; ++i)
        {
            for (int j = 0; j < ma; ++j)
            {
                sum.data[i][j] = mat.data[i][j] + data[i][j];
            }
        }
        return sum;
    }

    Matrix<T> operator-(const Matrix<T> &mat) const
    {
        int na = mat.n;
        int ma = mat.m;
        auto minus = zero_matrix(na, ma);
        for (int i = 0; i < na; ++i)
        {
            for (int j = 0; j < ma; ++j)
            {
                minus.data[i][j] = mat.data[i][j] - data[i][j];
            }
        }
        return minus;
    }

    Matrix<T> operator*(const int k) const
    {
        auto ans = zero_matrix(n, m);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                ans.data[i][j] = k * data[i][j];
            }
        }
        return ans;
    }

    Matrix<T> operator*(const Matrix<T> &mat) const
    {
        int na = n;
        int ka = m;
        int ma = mat.m;
        auto ans = zero_matrix(na, ma);
        for (int i = 0; i < na; ++i)
        {
            for (int j = 0; j < ma; ++j)
            {
                ans.data[i][j] = 0;
                for (int k = 0; k < ka; ++k)
                {
                    ans.data[i][j] = ans.data[i][j] + data[i][k] * mat.data[k][j];
                }
            }
        }
        return ans;
    }

    Matrix<T> operator^(const int k) const
    {
        auto ans = (*this);
        for (int i = 0; i < k - 1; ++i)
        {
            ans = ans * (*this);
        }
        return ans;
    }

    static Matrix<T> Kronecker_product(Matrix<T> &a, Matrix<T> &b)
    {
        int p = a.n * b.n;
        int q = a.m * b.m;
        auto ans = zero_matrix(p+1, q+1);
        for (int i = 0; i < a.n; ++i)
        {
            for (int k = 0; k < b.n; ++k)
            {
                for (int j = 0; j < a.m; ++j)
                {
                    for (int l = 0; l < b.m; ++l)
                    {
                        ans.data[i + l + 1][j + k + 1] = a.data[i][j] * b.data[k][l];
                    }
                }
            }
        }
        auto ans1 = zero_matrix(p,q);
        for(size_t i = 0; i < p; ++i){
            for(size_t j = 0; j < q; ++j){
                ans1.data[i][j] = ans.data[i+1][j+1];
            }
        }
        return ans1;
    }

    friend std::ostream &operator<<(std::ostream &out, const Matrix<T> &mat)
    {
        out << '\n';
        for (int i = 0; i < mat.n; ++i)
        {
            for (int j = 0; j < mat.m; ++j)
            {
                out << mat.data[i][j] << " ";
            }
            out << '\n';
        }
        return out;
    }

};

#endif