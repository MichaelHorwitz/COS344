#include "Matrix.h"
Matrix::~Matrix(){
    for (int i = 0; i < n; ++i) {
        delete [] arr[i];
    }
    delete [] arr;
}
Matrix::Matrix(int n, int m){
    if (n < 0 || m <0)
    {
        throw MathExceptions::InvalidMatrixSize;
    }
    
    arr = new double*[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = new double[m];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            arr[i][j] = 0;
        }
        
    }
}

Matrix::Matrix(int n, int m, double ** arr){
    this->n = n;
    this->m = m;
    this->arr = arr;
}
Matrix::Matrix::Matrix(const Matrix& inMatrix){
    m = inMatrix.m;
    n = inMatrix.n;
    arr = new double*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new double[m];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[i][j] = inMatrix.arr[i][j];
        }
    }
}

int Matrix::getM() const {
    return m;
}

int Matrix::getN() const {
    return n;
}

SquareMatrix::SquareMatrix(int n) : Matrix(n, n){

}

SquareMatrix::SquareMatrix(int n, double ** arr) : Matrix(n, n, arr){

}

SquareMatrix::~SquareMatrix() {

}

IdentityMatrix::IdentityMatrix(int n) : SquareMatrix(n){
    for (int i = 0; i < n; ++i) {
        arr[i][i] = 1;
    }
}

IdentityMatrix::~IdentityMatrix() {

}
