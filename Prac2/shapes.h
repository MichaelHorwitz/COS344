#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Matrix.h"
#include "Vector.h"

using namespace glm;
using namespace std;


struct Shape{
    Vector** vertices;
    Vector** colors;
    Shape** shapes;
    int numShapes;

    ~Shape();

    virtual void applyMatrix(Matrix);
    virtual GLfloat* toVertexArray();
    virtual GLfloat* toColorArray();
    virtual int numPoints();

    virtual int numVertices();
    virtual int numColors();
};

struct Triangle: public Shape{
    Triangle(Vector, Vector, Vector, Vector);
    int numVertices();
    int numColors();
    int numPoints();
};

struct Rectangle: public Shape{
    Rectangle(Vector, Vector, Vector, Vector, Vector);
};

struct Circle: public Shape{
    int numVertices;
    double length;
    Circle(int, double, double, double, Vector);
};

struct Car: public Shape{
    Car();
};

#endif /*SHAPES_H*/