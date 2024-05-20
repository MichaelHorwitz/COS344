#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "NewMathLibrary/Matrix.h"
#include "NewMathLibrary/Vector.h"
#include "Vector.h"

using namespace glm;
using namespace std;


struct Shape{
    Vector3** vertices;
    Vector4** colors;
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
    Triangle(Vector3z, Vector3, Vector3, Vector4);
    int numVertices();
    int numColors();
    int numPoints();
};

struct Rectangle: public Shape{
    Rectangle(Vector, Vector, Vector, Vector, Vector);
};


#endif /*SHAPES_H*/