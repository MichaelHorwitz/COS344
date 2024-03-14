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

Matrix Matrix::operator*(const Matrix matrix) const {
    if (m != matrix.n) {
        throw MathExceptions::InvalidMatrixMultiplication;
    }
    Matrix newMatrix(n, matrix.m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < matrix.m; ++j) {
            double curr = 0;
            for (int k = 0; k < m; ++k) {
                curr += arr[i][k] * arr[k][j];
            }
        }
    }
    return newMatrix;
}

Matrix Matrix::operator*(const double s) const {
    Matrix newMatrix(n, m, arr);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            newMatrix[i][j] *= s;
        }
    }
    return newMatrix;
}

Matrix Matrix::operator+(const Matrix matrix) const {
    Matrix newMatrix(n, m, arr);
    if (n != matrix.n || m != matrix.m){
        throw MathExceptions::InvalidMatrixAddition;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            newMatrix.arr[i][j] += matrix.arr[i][j];
        }
    }
    return newMatrix;
}

Matrix Matrix::operator~() const {
    Matrix newMatrix(m, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            newMatrix.arr[j][i] = arr[i][j];
        }
    }
    return newMatrix;
}



SquareMatrix::SquareMatrix(int n) : Matrix(n, n){

}

SquareMatrix::SquareMatrix(int n, double ** arr) : Matrix(n, n, arr){

}

SquareMatrix::~SquareMatrix() {

}

SquareMatrix SquareMatrix::operator!() const {
    SquareMatrix newMatrix(n, arr);
    IdentityMatrix idMatrix(n);
    //For every nth row
    for (int currElem = 0; currElem < n; ++currElem) {
        //divide to get 1 at the begining
        for (int j = 0; j < n; ++j) {
            double divisor = arr[0][j];
            arr[currElem][j] /= divisor;
            idMatrix.arr[currElem][j] /= divisor;
        }
        //Subtract from every row below
        for (int row = currElem; row < n; ++row) {
            double multiplier = arr[row][currElem];
            for (int col = 0; col < n; ++col) {
                arr[row][col] -= arr[currElem][col] * multiplier;
                idMatrix.arr[row][col] -= idMatrix[currElem][col] * multiplier;
            }
        }
    }
    for (int currElem = n - 2; currElem >= 0; --currElem) {
        for (int row = currElem; row >= 0; --row) {
            double multiplier = arr[row][currElem];
            for (int col = n-1; col >= currElem; --col) {
                arr[row][col] -= arr[currElem][col] * multiplier;
                idMatrix.arr[row][col] -= idMatrix[currElem][col] * multiplier;
            }
        }
    }
    return idMatrix;
}

double SquareMatrix::determinant() const {
    return 0;
}
double recDeterminant(double** arr, int n){
    if (n == 2){
        return arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0];
    }
    double deter = 0;
    for (int i = 0; i < n; ++i) {
        int newN = n-1;
        double** newArr = new double*[newN];
        for (int row = 1; row < n; ++row) {
            newArr[row - 1] = new double [newN];
            for (int col = 0; col < n; ++col) {
                if (col < n){
                    newArr[row - 1][col] = arr[row][col];
                } else if (col > n){
                    newArr[row - 1][col - 1] = arr[row][col];
                }

            }
        }
        if (i % 2 == 0){
            deter += arr[0][i] * recDeterminant(newArr, newN);
        } else {
            deter -= arr[0][i] * recDeterminant(newArr, newN);
        }
    }
    return deter;
}

IdentityMatrix::IdentityMatrix(int n) : SquareMatrix(n){
    for (int i = 0; i < n; ++i) {
        arr[i][i] = 1;
    }
}

IdentityMatrix::~IdentityMatrix() {

}
