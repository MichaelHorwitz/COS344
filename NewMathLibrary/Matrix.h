#pragma once
#include <iostream>
#include <cmath>
#include <iomanip>

#include "Vector.h"
#include "MathExceptions.h"

class Vector;

class Matrix
{
protected:
    int n;
    int m;
    double **arr;

public:
    Matrix();
    Matrix(int, int);
    Matrix(int, int, double **);
    Matrix(const Matrix &);
    virtual ~Matrix();
    double *&operator[](int index) const
    {
        if (index >= n || index < 0)
            throw MathExceptions::InvalidIndex;


        return arr[index];
    }
    Matrix operator*(const Matrix) const;
    Matrix operator*(const double) const;
    Matrix operator+(const Matrix) const;
    Matrix operator~() const;
    void print() const
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                std::cout << (*this)[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    int getM() const;
    int getN() const;
    double ** getArr(){return arr;};
    Vector* toVector();
};

class SquareMatrix : public Matrix
{
public:
    SquareMatrix();
    explicit SquareMatrix(int);
    SquareMatrix(int, double **);
    //void upperTriangular(Vector&) const;
    ~SquareMatrix() override;
    Vector solve(const Vector) const;
    double determinant() const;
    SquareMatrix operator!() const;
};

class Matrix4x4 : public SquareMatrix{
public:
    Matrix4x4();
    explicit Matrix4x4(double);
    static Matrix4x4 convertTo4x4(Matrix matrix);
};

class IdentityMatrix : public SquareMatrix
{
public:
    explicit IdentityMatrix(int);
    ~IdentityMatrix() override;
};