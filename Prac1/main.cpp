#include "Vector.h"
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
int main(){
    //dotProduct();
    //crossProduct();
    transpose();
}