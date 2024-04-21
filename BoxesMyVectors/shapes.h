#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Matrix.h"

using namespace std;


struct Shape{
    Vector** vertices;
    Vector* colors;
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

struct Box: public Shape{
    Box(Vector center, double height, double width, double length, Vector);
};

struct Boxes: public Shape{
    Boxes(int numBoxes, Vector* centers, double* heights, double* widths, double* lengths, Vector* colors);
};

#endif /*SHAPES_H*/