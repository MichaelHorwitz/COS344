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
        for (int i = 0; i < numPoints(); i++)
        {
            result[count++] = (*vertices[i])[0];
            result[count++] = (*vertices[i])[1];
            result[count++] = (*vertices[i])[2];
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
        for (int i = 0; i < numPoints(); i++)
        {
            result[count++] = colors[i][0];
            result[count++] = colors[i][1];
            result[count++] = colors[i][2];
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
            //(*vertices[i]) = m * vec4((*vertices[i]), 1);
            Matrix tempVector = Matrix(4, 1);
            for (size_t j = 0; j < 3; j++)
            {
                Vector * currVector = vertices[i];
                tempVector[i][0] = currVector->operator[](j);
            }
            tempVector[3][0] = 1;
            vertices[i] = (m * tempVector).toVector();
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

    int n = numPoints();
    vertices = new Vector *[n];
    vertices[0] = new Vector(point1);
    vertices[1] = new Vector(point2);
    vertices[2] = new Vector(point3);

    colors = new Vector[n];
    for (int i = 0; i < 3; i++)
    {
        colors[i] = color;
    }
}

int Triangle::numVertices()
{
    return 9;
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

    colors = new Vector[n];

    for (int i = 0; i < n; i++)
    {
        colors[i] = color;
    }
}


Box::Box(Vector center, double height, double width, double length, Vector color)
{

    double* arr = new double[3];
    arr[0] = 0; arr[1] = height / 2; arr[2] = 0;
    Vector topPlane = center + Vector(3, arr);

    arr = new double[3];
    arr[0] = 0; arr[1] = height / 2; arr[2] = 0;
    Vector bottomPlane = center - Vector(3, arr);

    arr = new double[3];
    arr[0] = width / 2; arr[1] = 0; arr[2] = 0;
    Vector leftPlane = center - Vector(3, arr);

    arr = new double[3];
    arr[0] = width / 2; arr[1] =0; arr[2] = 0;
    Vector rightPlane = center + Vector(3, arr);

    arr = new double[3];
    arr[0] = 0; arr[1] = 0; arr[2] = length / 2;
    Vector nearPlane = center - Vector(3, arr);

    arr = new double[3];
    arr[0] = 0; arr[1] = 0; arr[2] = length / 2;
    Vector farPlane = center + Vector(3, arr);

    Vector nearLeftTop = nearPlane + leftPlane + topPlane;
    Vector nearRightTop = nearPlane + rightPlane + topPlane;
    Vector nearLeftBottom = nearPlane + leftPlane + bottomPlane;
    Vector nearRightBottom = nearPlane + rightPlane + bottomPlane;

    Vector farLeftTop = farPlane + leftPlane + topPlane;
    Vector farRightTop = farPlane + rightPlane + topPlane;
    Vector farLeftBottom = farPlane + leftPlane + bottomPlane;
    Vector farRightBottom = farPlane + rightPlane + bottomPlane;

    Rectangle *front = new Rectangle(nearLeftTop, nearRightTop, nearLeftBottom, nearRightBottom, color*0.1f);
    Rectangle *back = new Rectangle(farRightTop, farLeftTop, farRightBottom, farLeftBottom, color*0.2f);
    Rectangle *left = new Rectangle(farLeftTop, nearLeftTop, farLeftBottom, nearLeftBottom, color*0.3f);
    Rectangle *right = new Rectangle(nearRightTop, farRightTop, nearRightBottom, farRightBottom, color*0.4f);
    Rectangle *bottom = new Rectangle(nearLeftBottom, nearRightBottom, farLeftBottom, farRightBottom, color*0.5f);
    Rectangle *top = new Rectangle(nearLeftTop, nearRightTop, farLeftTop, farRightTop, color*0.6f);

    numShapes = 6;
    shapes = new Shape *[numShapes]
    {
        front, back, left, right, bottom, top
    };
}

Boxes::Boxes(int numBoxes, Vector *centers, double *heights, double *widths, double *lengths, Vector *colors)
{
    numShapes = numBoxes;
    shapes = new Shape*[numShapes];
    for(int i=0; i < numShapes; i++){
        shapes[i] = new Box(centers[i],heights[i], widths[i], lengths[i], colors[i]);
    }
}
