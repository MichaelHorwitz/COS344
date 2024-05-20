#include "Matrix.h"
Matrix::~Matrix(){
    for (int i = 0; i < n; ++i) {
        //delete [] arr[i];
    }
    //delete [] arr;
}
Matrix::Matrix(int n, int m){
    //std::cout << "Into constructor";
    this->n = n;
    this->m = m;
    if (n < 0 || m <0)
    {
        throw MathExceptions::InvalidMatrixSize;
        //return;
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
Matrix::Matrix(const Matrix& inMatrix){
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
                curr += arr[i][k] * matrix.arr[k][j];
            }
            newMatrix.arr[i][j] = curr;
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
    //std::cout << n;
    //std::cout << m;
    Matrix newMatrix(m, n);
    //std::cout << newMatrix.n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            newMatrix.arr[j][i] = arr[i][j];
            //std::cout << arr[i][j];
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

/*void SquareMatrix::upperTriangular(Vector& solutionVector) const{
    //For every nth row
    for (int currElem = 0; currElem < n; ++currElem) {
        //divide to get 1 at the begining
        for (int j = 0; j < n; ++j) {
            double divisor = arr[0][j];
            arr[currElem][j] /= divisor;
            solutionVector[currElem] /= divisor;
        }
        //Subtract from every row below
        for (int row = currElem; row < n; ++row) {
            double multiplier = arr[row][currElem];
            for (int col = 0; col < n; ++col) {
                arr[row][col] -= arr[currElem][col] * multiplier;
                solutionVector[row] -= solutionVector[currElem] * multiplier;
            }
        }
    }
}*/

SquareMatrix SquareMatrix::operator!() const {
    SquareMatrix newMatrix(n, arr);
    IdentityMatrix idMatrix(n);
    //For every nth row
    for (int currElem = 0; currElem < n; ++currElem) {
//        std::cout << "###" << std::endl;
//        newMatrix.print();
//        idMatrix.print();
//        std::cout << "###" << std::endl;
        //divide to get 1 at the begining
        double divisor = newMatrix.arr[currElem][currElem];
        for (int j = 0; j < n; ++j) {
            //double divisor = newMatrix.arr[currElem][currElem];
            newMatrix.arr[currElem][j] /= divisor;
            idMatrix.arr[currElem][j] /= divisor;
        }
        //Subtract from every row below
        for (int row = currElem + 1; row < n; ++row) {
            double multiplier = arr[row][currElem];
            for (int col = 0; col < n; ++col) {
                newMatrix.arr[row][col] -= newMatrix.arr[currElem][col] * multiplier;
                idMatrix.arr[row][col] -= idMatrix[currElem][col] * multiplier;
            }
        }
    }
    for (int currElem = n - 2; currElem >= 0; --currElem) {
        for (int row = currElem; row >= 0; --row) {
            double multiplier = newMatrix.arr[row][currElem];
            for (int col = n-1; col > currElem; --col) {
                newMatrix.arr[row][col] -= newMatrix.arr[currElem][col] * multiplier;
                idMatrix.arr[row][col] -= idMatrix[currElem][col] * multiplier;
            }
        }
    }
//    newMatrix.print();
    return idMatrix;
}

double recDeterminant(double** arr, int n){
    if (n == 1){
        return arr[0][0];
    }
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
                if (col < i){
                    newArr[row - 1][col] = arr[row][col];
                } else if (col > i){
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

double SquareMatrix::determinant() const {
    return recDeterminant(arr, n);
}

Vector SquareMatrix::solve(const Vector inVector) const {
    Vector solutionVector(inVector);
    for (int currElem = 0; currElem < n; ++currElem) {
        //divide to get 1 at the begining
        for (int j = 0; j < n; ++j) {
            double divisor = arr[0][j];
            arr[currElem][j] /= divisor;
            solutionVector[currElem] /= divisor;
        }
        //Subtract from every row below
        for (int row = currElem; row < n; ++row) {
            double multiplier = arr[row][currElem];
            for (int col = 0; col < n; ++col) {
                arr[row][col] -= arr[currElem][col] * multiplier;
                solutionVector[row] -= solutionVector[currElem] * multiplier;
            }
        }
    }
    SquareMatrix tempSM(*this);
    for (int row = n-1; row >= 0; ++row) {
        for (int col = n-1; col >= row; ++col) {
            solutionVector[col] = solutionVector[col] - tempSM[row][col];
        }
    }
    return solutionVector;
}

SquareMatrix::SquareMatrix() {
    this->n = 0;
    this->arr = new double * [0];
}


IdentityMatrix::IdentityMatrix(int n) : SquareMatrix(n){
    for (int i = 0; i < n; ++i) {
        arr[i][i] = 1;
    }
}

IdentityMatrix::~IdentityMatrix() {

}
Vector* Matrix::toVector() {
    double * arr = new double[this->n];
    for (int i = 0; i < n; ++i) {
        arr[i] = this->arr[i][0];
        //std::cout << "CURR ARR: " << arr[i] << std::endl;
    }
    Vector * newVector = new Vector(this->n, arr);
    return newVector;
}

Matrix::Matrix() {
    this->n = 0;
    this->m = 0;
    this->arr = new double * [0];

}

Matrix4x4::Matrix4x4() {
    this->n = this->m = 4;
    this->arr = new double * [4];
    for (int i = 0; i < 4; ++i) {
        arr[i] = new double[4];
        for (int j = 0; j < 4; ++j) {
            arr[i][j] = 0;
        }
    }
}

Matrix4x4::Matrix4x4(double fill) {
    this->n = this->m = 4;
    this->arr = new double * [4];
    for (int i = 0; i < 4; ++i) {
        this->arr[i] = new double[4];
        for (int j = 0; j < 4; ++j) {
            this->arr[i][j] = fill;
        }
    }
}

Matrix4x4 Matrix4x4::convertTo4x4(Matrix matrix) {
    Matrix4x4 ret = Matrix4x4();
    ret.n = matrix.getN();
    ret.m = matrix.getM();
    ret.arr = matrix.getArr();
    return ret;
}

