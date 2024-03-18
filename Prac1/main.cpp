#include "Vector.h"
#include <cstdlib>
void dotProduct(){
    //double arr1[] = {-1, 0, 1};
    //double arr2[] = {1, 2, 3};
    const int n = 3;
    Vector v1(n);
    Vector v2(n);
    v1[0] = -1;
    v1[1] = 0;
    v1[2] = 1;
    v2[0] = 1;
    v2[1] = 2;
    v2[2] =3;
    double v3 = v1 * v2;
    std::cout << v3;
}
void crossProduct(){
    const int n = 3;
    Vector v1(n);
    Vector v2(n);
    v1[0] = -1;
    v1[1] = 0;
    v1[2] = 1;
    v2[0] = 1;
    v2[1] = 2;
    v2[2] =3;
    Vector v3 = v1.crossProduct(v2);
    v3.print();
}
void transpose(){
    int n = 2, m = 3;
    auto arr = new double * [n];
    for (int i = 0; i < n; ++i) {
        arr[i] = new double[m];
        for (int j = 0; j < m; ++j) {
            arr[i][j] = i + j;
        }
    }
    Matrix matrix(2, 3, arr);
    matrix.print();
    (~matrix).print();
    matrix = ~matrix;
    matrix.print();
}
void inverse(){
    int n = 2;
    auto arr = new double * [n];
    for (int i = 0; i < n; ++i) {
        arr[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            arr[i][j] = i + j + 1;
        }
    }
    SquareMatrix matrix(n, arr);
    matrix.print();
    (!matrix).print();
}
void multiply(){
    int n = 2;
    int m = 3;
    auto ** arr1 = new double * [n];
    auto ** arr2 = new double * [m];

    for (int i = 0; i < n; ++i) {
        arr1[i] = new double[m];
        for (int j = 0; j < m; ++j) {
            arr1[i][j] = i + j + 1;
        }
    }

    for (int i = 0; i < m; ++i) {
        arr2[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            arr2[i][j] = i + j - 3;
        }
    }

    Matrix matrix(n,m, arr1);
    matrix.print();
    Matrix matrix2(m,n, arr2);
    matrix2.print();
    Matrix matrix3 = matrix * matrix2;
    matrix3.print();
}
void determinant(){
    srand(time(0));

    int n = 3;
    auto arr = new double * [n];
    for (int i = 0; i < n; ++i) {
        arr[i] = new double [n];
        for (int j = 0; j < n; ++j) {
            //arr[i][j] = i + j + 1;
            arr[i][j] = rand() % 10;
        }
    }
    SquareMatrix matrix(n, arr);
    matrix.print();
    double deter = matrix.determinant();
    std::cout << deter;
}
int main(){
    //dotProduct();
    //crossProduct();
    //transpose();
    //inverse();
    //multiply();
    determinant();
}
