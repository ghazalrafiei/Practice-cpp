#include<iostream>
#include "matrix.h"

int main(){
    typedef std::vector<std::vector<int>> vector_int;
    typedef std::vector<std::vector<double>> vector_double;

    vector_int a = {{2,4},{4,2}};
    vector_int b = {{9,8},{7,6}};

    Matrix<int> A = Matrix<int>(a);
    Matrix<int> B = Matrix<int>(b);
    
    Matrix<int> C = A + B ;
    std::cout<<C;

    Matrix<int> D = B*2;
    std::cout<<D;

    Matrix<int> K = Matrix<int>::Kronecker_product(A , B);
    std::cout<<K;

    Matrix<int> P = A^3;
    std::cout<<P;
    













    return 0;
}