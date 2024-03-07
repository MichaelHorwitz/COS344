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
