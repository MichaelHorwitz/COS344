#include "shapes.h"

Shape::~Shape()
{

}

int Shape::numPoints()
{
    int count = 0;
    for (int i = 0; i < numShapes; i++)
    {
        count += shapes[i]->numPoints();
    }
    return count;
}

GLfloat *Shape::toVertexArray()
{
    int n = numVertices();
    GLfloat *result = new GLfloat[numVertices()];
    if (numShapes > 0)
    {
        int count = 0;
        for (int i = 0; i < numShapes; i++)
        {
            GLfloat *temp = shapes[i]->toVertexArray();
            for (int j = 0; j < shapes[i]->numVertices(); j++)
            {
                result[count++] = temp[j];
            }
            delete[] temp;
        }
    }
    else
    {
        int count = 0;
        for (int i = 0; i < numVertices() / 2; i++)
        {
            result[count++] = (*vertices[i])[0];
            result[count++] = (*vertices[i])[1];
        }
    }

    return result;
}

GLfloat *Shape::toColorArray()
{
    GLfloat *result = new GLfloat[numColors()];
    if (numShapes > 0)
    {
        int count = 0;
        for (int i = 0; i < numShapes; i++)
        {
            GLfloat *temp = shapes[i]->toColorArray();
            for (int j = 0; j < shapes[i]->numColors(); j++)
            {
                result[count++] = temp[j];
            }
            delete[] temp;
        }
    }
    else
    {
        int count = 0;
        for (int i = 0; i < numVertices() / 2; i++)
        {
            std::cout << "COUNT: " << count << std::endl;
            result[count++] = colors[i]->operator[](0);
            result[count++] = colors[i]->operator[](1);
            result[count++] = colors[i]->operator[](2);
        }
    }
    return result;
}

void Shape::applyMatrix(Matrix m)
{
    if (numShapes > 0)
    {
        for (int i = 0; i < numShapes; i++)
        {
            shapes[i]->applyMatrix(m);
        }
    }
    else
    {

        for (int i = 0; i < numPoints(); i++)
        {
            std::cout << "VERTEX " << i << std::endl;
            vertices[i]->print();
            Matrix tempVector = Matrix(3,1);
            for (int j = 0; j < 2; ++j) {
                tempVector[j][0] = vertices[i]->operator[](j);
            }
            tempVector[2][0] = 1;
            std::cout << "TEMPVECTOR" << std::endl;
            tempVector.print();
            //(*vertices[i]) = m * vec3((*vertices[i]), 1);
            Matrix tempMatrix = (m * tempVector);
            std::cout << "TEMPMATRIX" << std::endl;
            tempMatrix.print();
            tempMatrix.toVector()->print();

            //(*vertices[i]) = tempMatrix.toVector();
            vertices[i] = tempMatrix.toVector();

        }
    }
}

int Shape::numVertices()
{
    int count = 0;
    for (int i = 0; i < numShapes; i++)
    {
        count += shapes[i]->numVertices();
    }
    return count;
}

int Shape::numColors()
{
    int count = 0;
    for (int i = 0; i < numShapes; i++)
    {
        count += shapes[i]->numColors();
    }
    return count;
}

Triangle::Triangle(Vector point1, Vector point2, Vector point3, Vector color)
{
    numShapes = 0;
    shapes = new Shape *[0];
    point1.print();
    int n = 3;//numPoints();
    vertices = new Vector *[n];
    vertices[0] = new Vector(point1);
    vertices[1] = new Vector(point2);
    vertices[2] = new Vector(point3);


    colors = new Vector * [n];
    for (int i = 0; i < 3; i++)
    {
        colors[i] = &color;
    }
}

int Triangle::numVertices()
{
    return 6;
}

int Triangle::numColors()
{
    return 9;
}

int Triangle::numPoints()
{
    return 3;
}

Rectangle::Rectangle(Vector ul, Vector ur, Vector ll, Vector lr, Vector color)
{
    numShapes = 2;
    shapes = new Shape *[numShapes];
    shapes[0] = new Triangle(ur, ul, ll, color);
    shapes[1] = new Triangle(ll, lr, ur, color);
    int n = numPoints();
    vertices = new Vector *[n];
    int count = 0;
    for (int i = 0; i < numShapes; i++)
    {
        for (int j = 0; j < shapes[i]->numPoints(); j++)
        {
            vertices[count++] = shapes[i]->vertices[j];
        }
    }

    colors = new Vector* [n];

    for (int i = 0; i < n; i++)
    {
        colors[i] = &color;
    }
}

Car::Car()
{
    numShapes = 1;
    Vector v1 = Vector(2);
    v1[0] = -0.5;
    v1[1] = 0;

    Vector v2 = Vector(2);
    v2[0] = 0;
    v2[1] = 0.25;

    Vector v3 = Vector(2);
    v3[0] = 0.5;
    v3[1] = 0;

    Vector colVector = Vector(3);
    colVector[0] = 0.7;
    colVector[1] = 0.7;
    colVector[2] = 0.3;
    shapes[0] = new Triangle(v1, v2, v3, colVector);
//    numShapes = 3;
//    shapes = new Shape *[numShapes];
//    shapes[0] = new Triangle(
//        vec2(0, 0.4),
//        vec2(-0.2, 0.2),
//        vec2(0.2, 0.2));
//    shapes[1] = new Rectangle(
//        vec2(-0.2, 0.2),
//        vec2(0.2, 0.2),
//        vec2(-0.2, -0.2),
//        vec2(0.2, -0.2));
//    shapes[2] = new Rectangle(
//        vec2(-0.05, 0),
//        vec2(0.05, 0),
//        vec2(-0.05, -0.2),
//        vec2(0.05, -0.2),
//        vec3(0, 0, 1));
}