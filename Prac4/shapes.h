#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "NewMathLibrary/Matrix.h"
#include "NewMathLibrary/Vector.h"

using namespace std;


struct Shape{
    Vector3** vertices;
    Vector4** colors;
    Shape** shapes;
    int numShapes;

    ~Shape();
    Shape();
    virtual void applyMatrix(Matrix);
    virtual GLfloat* toVertexArray();
    virtual GLfloat* toColorArray();
    virtual int numPoints();

    virtual int numVertices();
    virtual int numColors();

    virtual Shape* addShape(Shape*);
    virtual void changeColor(Vector4);
};

struct Triangle: public Shape{
    Triangle(Vector3, Vector3, Vector3, Vector4);
    int numVertices();
    int numColors();
    int numPoints();
};

struct Rectangle: public Shape{
    Rectangle(Vector3, Vector3, Vector3, Vector3, Vector4);
};
struct BackSheet: public Shape{
    BackSheet(Vector3, Vector3, Vector3, Vector3, Vector4, Vector4, int);
    BackSheet(Vector3, Vector3, Vector3, Vector3, Vector4, int);
};
struct Cuboid: public Shape{
    Cuboid(Vector3, Vector3, Vector3, Vector3, float, Vector4);
};
#endif /*SHAPES_H*/