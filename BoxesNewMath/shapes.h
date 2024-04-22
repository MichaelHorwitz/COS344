#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../NewMathLibrary/Matrix.h"
#include "../NewMathLibrary/Vector.h"

using namespace std;


struct Shape{
    Vector3** vertices;
    Vector3* colors;
    Shape** shapes;
    int numShapes;

    ~Shape();

    virtual void applyMatrix(Matrix4x4);
    virtual GLfloat* toVertexArray();
    virtual GLfloat* toColorArray();
    virtual int numPoints();

    virtual int numVertices();
    virtual int numColors();
};

struct Triangle: public Shape{
    Triangle(Vector3, Vector3, Vector3, Vector3 = Vector3(1.0f, 0.0f, 0.0f));
    int numVertices();
    int numColors();
    int numPoints();
};

struct Rectangle: public Shape{
    Rectangle(Vector3, Vector3, Vector3, Vector3, Vector3 = Vector3(0.0f, 1.0f, 0.0f));
};

struct Box: public Shape{
    Box(Vector3 center, double height, double width, double length, Vector3 = Vector3(1.0f, 0.2f, 0.2f));
};

struct Boxes: public Shape{
    Boxes(int numBoxes, Vector3* centers, double* heights, double* widths, double* lengths, Vector3* colors);
};

struct House: public Shape{
    House();
};

#endif /*SHAPES_H*/