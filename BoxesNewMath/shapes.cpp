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

void Shape::applyMatrix(Matrix4x4 m)
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
            Matrix tempMatrix = m * Vector4((*vertices[i]), 1);
            (*vertices[i]) = tempMatrix;
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

Triangle::Triangle(Vector3 point1, Vector3 point2, Vector3 point3, Vector3 color)
{
    numShapes = 0;
    shapes = new Shape *[0];

    int n = numPoints();
    vertices = new Vector3 *[n];
    vertices[0] = new Vector3(point1);
    vertices[1] = new Vector3(point2);
    vertices[2] = new Vector3(point3);

    colors = new Vector3[n];
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

Rectangle::Rectangle(Vector3 ul, Vector3 ur, Vector3 ll, Vector3 lr, Vector3 color)
{
    numShapes = 2;
    shapes = new Shape *[numShapes];
    shapes[0] = new Triangle(ur, ul, ll, color);
    shapes[1] = new Triangle(ll, lr, ur, color);
    int n = numPoints();
    vertices = new Vector3 *[n];
    int count = 0;
    for (int i = 0; i < numShapes; i++)
    {
        for (int j = 0; j < shapes[i]->numPoints(); j++)
        {
            vertices[count++] = shapes[i]->vertices[j];
        }
    }

    colors = new Vector3[n];

    for (int i = 0; i < n; i++)
    {
        colors[i] = color;
    }
}

House::House()
{
    numShapes = 3;
    shapes = new Shape *[numShapes];
    shapes[0] = new Triangle(
        Vector3(0, 0.4, 0),
        Vector3(-0.2, 0.2, 0),
        Vector3(0.2, 0.2, 0));
    shapes[1] = new Rectangle(
        Vector3(-0.2, 0.2, 0),
        Vector3(0.2, 0.2, 0),
        Vector3(-0.2, -0.2, 0),
        Vector3(0.2, -0.2, 0));
    shapes[2] = new Rectangle(
        Vector3(-0.05, 0, 0),
        Vector3(0.05, 0, 0),
        Vector3(-0.05, -0.2, 0),
        Vector3(0.05, -0.2, 0),
        Vector3(0, 0, 1));
}

Box::Box(Vector3 center, double height, double width, double length, Vector3 color)
{
    Vector3 topPlane = center + Vector3(0, height / 2, 0);
    Vector3 bottomPlane = center - Vector3(0, height / 2, 0);
    Vector3 leftPlane = center - Vector3(width / 2, 0, 0);
    Vector3 rightPlane = center + Vector3(width / 2, 0, 0);
    Vector3 nearPlane = center - Vector3(0, 0, length / 2);
    Vector3 farPlane = center + Vector3(0, 0, length / 2);

    Vector3 nearLeftTop = nearPlane + leftPlane + topPlane;
    Vector3 nearRightTop = nearPlane + rightPlane + topPlane;
    Vector3 nearLeftBottom = nearPlane + leftPlane + bottomPlane;
    Vector3 nearRightBottom = nearPlane + rightPlane + bottomPlane;

    Vector3 farLeftTop = farPlane + leftPlane + topPlane;
    Vector3 farRightTop = farPlane + rightPlane + topPlane;
    Vector3 farLeftBottom = farPlane + leftPlane + bottomPlane;
    Vector3 farRightBottom = farPlane + rightPlane + bottomPlane;

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

Boxes::Boxes(int numBoxes, Vector3 *centers, double *heights, double *widths, double *lengths, Vector3 *colors)
{
    numShapes = numBoxes;
    shapes = new Shape*[numShapes];
    for(int i=0; i < numShapes; i++){
        shapes[i] = new Box(centers[i],heights[i], widths[i], lengths[i], colors[i]);
    }
}
