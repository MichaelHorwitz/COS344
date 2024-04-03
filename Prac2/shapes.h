#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;
using namespace std;


struct Shape{
    vec2** vertices;
    vec3* colors;
    Shape** shapes;
    int numShapes;

    ~Shape();

    virtual void applyMatrix(mat3x3);
    virtual GLfloat* toVertexArray();
    virtual GLfloat* toColorArray();
    virtual int numPoints();

    virtual int numVertices();
    virtual int numColors();
};

struct Triangle: public Shape{
    Triangle(vec2, vec2, vec2, vec3 = vec3(1.0f, 0.0f, 0.0f));
    int numVertices();
    int numColors();
    int numPoints();
};

struct Rectangle: public Shape{
    Rectangle(vec2, vec2, vec2, vec2, vec3 = vec3(0.0f, 1.0f, 0.0f));
};

struct House: public Shape{
    House();
};

#endif /*SHAPES_H*/