#include "Vector.h"

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
    this->arr = arr;
}

Vector::~Vector()
{
    delete [] arr;
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
