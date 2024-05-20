#pragma once

#include "Matrix.h"
#include "MathExceptions.h"

class Matrix;
class Vector3;
class Vector
{
protected:
    int n;       // size of the vector
    double *arr; // array containing the elements in the vector

public:
    Vector();
    Vector(int);
    Vector(int, double *);
    ~Vector();
    Vector(const Vector &);
    // add conversion from Vector to Vector3
    operator Vector3() const;
    Vector operator+(const Vector) const;
    Vector operator-(const Vector) const;
    Vector operator*(const double) const;
    double operator*(const Vector) const;
    double &operator[](int index) const
    {
        if (index < 0 || index >= n)
        {
            throw MathExceptions::InvalidIndex;
        }
        return arr[index];
    }
    double magnitude() const;
    operator Matrix() const;
    Vector crossProduct(const Vector) const;
    Vector unitVector() const;
    int getN() const;
    void print() const
    {
        for (int i = 0; i < n; i++)
        {
            std::cout<< arr[i] << "\n";
        }
    };
    Matrix toMatrix();
};

class Vector3 : public Vector {
public:
    Vector3();
    Vector3(double, double, double);
    Vector3(double *);
    operator Matrix() const;
    Vector3 operator= (Matrix) const;
};
class Vector4 : public Vector {
public:
    Vector4();
    Vector4(double, double, double, double);
    Vector4(double *);
    Vector4(Vector3, double);
};