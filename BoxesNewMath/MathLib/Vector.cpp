#include "Vector.h"
Vector::Vector(){
    int n = 0;
    arr = new double[n];
    this->n = n;
    for (int i = 0; i < n; i++)
    {
        arr[i] = 0.0;
    }
}

Vector::Vector(int n)
{
    if (n < 0)
    {
        throw MathExceptions::InvalidVectorSize;
    }
    
    arr = new double[n];
    this->n = n;
    for (int i = 0; i < n; i++)
    {
        arr[i] = 0.0;
    }
}

Vector::Vector(int n, double * arr)
{
    this->n = n;
    //arr = new double [3];
    this->arr = arr;
}

Vector::~Vector()
{
    //delete [] arr;
}

Vector::Vector(const Vector& inVector)
{
    n = inVector.n;
    arr = new double[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = inVector.arr[i];
    }
}

Vector Vector::operator+(const Vector w) const {
    if (this->n != w.n){
        throw MathExceptions::InvalidVectorAddition;
    }
    Vector newVector(this->n);
    for (int i = 0; i < n; ++i) {
        newVector.arr[i] = this->arr[i] + w.arr[i] ;
    }
    return newVector;
}

Vector Vector::operator-(const Vector w) const {
    if (this->n != w.n){
        throw MathExceptions::InvalidVectorAddition;
    }
    Vector newVector(this->n);
    for (int i = 0; i < n; ++i) {
        newVector.arr[i] = this->arr[i] - w.arr[i];
    }
    return newVector;
}

Vector Vector::operator*(const double s) const {
    Vector newVector(this->n);
    for (int i = 0; i < this->n; ++i) {
        newVector.arr[i] = this->arr[i] * s;
    }
    return newVector;
}

double Vector::operator*(const Vector w) const {
    if (this->n != w.n){
        throw MathExceptions::InvalidDotProduct;
    }
    double product = 0;
    for (int i = 0; i < n; ++i) {
        product += arr[i] * w.arr[i];
    }
    return product;
}

double Vector::magnitude() const {
    double sumOfSquares = 0;
    for (int i = 0; i < n; ++i) {
        sumOfSquares += arr[i] * arr[i];
    }
    return std::sqrt(sumOfSquares);
}

Vector Vector::crossProduct(const Vector w) const {
    if(n != 3 || w.n !=3){
        throw MathExceptions::InvalidCrossProduct;
    }
    Vector newVector(3);

    for (int i = 0; i < n; ++i) {
        int firstIndex = (i + 1) % 3, secondIndex = (i + 2) % 3;
        newVector.arr[i] = (arr[firstIndex] * w.arr [secondIndex]) - (arr[secondIndex] * w.arr[firstIndex]);
    }
    //newVector.arr[0] = arr[1] * w.arr[2] - arr[2] * w.arr[1];
    //newVector.arr[1] = arr[2] * w.arr[0] - arr[0] * w.arr[2];
    //newVector.arr[2] = arr[0] * w.arr[1] - arr[1] * w.arr[0];

    return newVector;
}

Vector Vector::unitVector() const {
    double mag = this->magnitude();
    Vector newVector(*this);
    for (int i = 0; i < n; ++i) {
        newVector.arr[i] /= mag;
    }
    return newVector;
}

int Vector::getN() const {
    return n;
}

Vector::operator Matrix() const {
    auto ** matrixArr = new double* [n];
    for (int i = 0; i < n; ++i) {
        matrixArr[i] = new double[1];
        matrixArr[i][0] = arr[i];
    }
    Matrix matrix(n, 1, matrixArr);
    return matrix;
}
Matrix Vector::toMatrix() {
    auto ** matrixArr = new double* [n];
    for (int i = 0; i < n; ++i) {
        matrixArr[i] = new double[1];
        matrixArr[i][0] = arr[i];
    }
    Matrix matrix(n, 1, matrixArr);
    return matrix;
}


Vector3::Vector3() {
    Vector(3);
}

Vector3::Vector3(double num1, double num2, double num3) {
    this->n = 3;
    arr = new double[3];
    arr[0] = num1;
    arr[1] = num2;
    arr[2] = num3;
}

Vector3::Vector3(double * arr) {
    this->n = 3;
    this->arr = arr;
}
