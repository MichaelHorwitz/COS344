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
    int numberOfColors = numColors();
    GLfloat *result = new GLfloat[numberOfColors];
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
            Matrix tempVector = Matrix(4,1);
            for (int j = 0; j < 2; ++j) {
                tempVector[j][0] = vertices[i]->operator[](j);
            }
            tempVector[3][0] = 1;
            Matrix tempMatrix = (m * tempVector);
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
    int n = 3;
    vertices = new Vector *[n];
    vertices[0] = new Vector(point1);
    vertices[1] = new Vector(point2);
    vertices[2] = new Vector(point3);


    colors = new Vector * [n];
    for (int i = 0; i < 3; i++)
    {
        colors[i] = new Vector(color);
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
    vertices = new Vector *[numPoints()];
    int count = 0;
    for (int i = 0; i < numShapes; i++)
    {
        for (int j = 0; j < shapes[i]->numPoints(); j++)
        {
            vertices[count++] = shapes[i]->vertices[j];
        }
    }

    colors = new Vector* [numPoints()];

    for (int i = 0; i < numPoints(); i++)
    {
        colors[i] = new Vector(color);
    }
}

Circle::Circle(int numVertices, double length, double x, double y, Vector colVector) {
    this->length = length;
    this->numShapes = numVertices - 2;
    this->numVertices = numShapes * 3;
    shapes = new Shape * [numShapes];
    this->colors = new Vector * [this->numVertices];
    vertices = new Vector * [this->numVertices];

    double spacing = 2.0 * M_PI / numVertices;
    Vector v1 = Vector(2);
    Vector v2 = Vector(2);
    Vector v3 = Vector(2);
    for (int i = 0; i < 3; ++i) {
        double angle = i * spacing;
        double * arr = new double[2];
        arr[0] = x + length * cos(angle);
        arr[1] = y + length * sin(angle);
        if (i == 0){
            v1 = Vector(2, arr);
        }
        if (i == 1){
            v2 = Vector(2, arr);
        }
        if (i == 2){
            v3 = Vector(2, arr);
        }
    }
    shapes[0] =  new Triangle(v1, v2, v3, colVector);
    for (int i = 3; i < numVertices; ++i) {
        double angle = i * spacing;
        double * arr = new double[2];
        arr[0] = x + length * cos(angle);
        arr[1] = y + length * sin(angle);
        v2 = v3;
        v3 = Vector(2, arr);
        shapes[i-2] = new Triangle(v1, v2, v3, colVector);
    }
    int count = 0;
    for (int i = 0; i < numShapes; i++)
    {
        for (int j = 0; j < shapes[i]->numPoints(); j++)
        {
            vertices[count++] = shapes[i]->vertices[j];
        }
    }
    colors = new Vector* [numPoints()];

    for (int i = 0; i < numPoints(); i++)
    {
        colors[i] = new Vector(colVector);
    }
}

Car::Car()
{
    numShapes = 9;
    shapes = new Shape*[numShapes];
    int currShape = 0;
    Vector v1 = Vector(2);
    Vector v2 = Vector(2);
    Vector v3 = Vector(2);
    Vector v4 = Vector(2);
    Vector colVector = Vector(3);

    //1 RECT BODY
    v1[0] = -0.75;
    v1[1] = 0;
    v2[0] = 0.75;
    v2[1] = 0;
    v3[0] = -0.75;
    v3[1] = -0.5;
    v4[0] = 0.75;
    v4[1] = -0.5;
    colVector[0] = 0.9;
    colVector[1] = 0.9;
    colVector[2] = 0.1;

    shapes[currShape++] = new Rectangle(v1, v2, v3, v4, colVector);

    //2 RECT TOP
    v1[0] = -0.50;
    v1[1] = 0.25;
    v2[0] = 0.30;
    v2[1] = 0.25;
    v3[0] = -0.50;
    v3[1] = 0;
    v4[0] = 0.30;
    v4[1] = 0;
    colVector[0] = 0.4;
    colVector[1] = 0.5;
    colVector[2] = 0.1;
    shapes[currShape++] = new Rectangle(v1, v2, v3, v4, colVector);

    //3 TRIG BODY
    v1[0] = 0.3;
    v1[1] = 0.25;
    v2[0] = 0.3;
    v2[1] = 0;
    v3[0] = 0.6;
    v3[1] = 0;
    colVector[0] = 0.4;
    colVector[1] = 0.5;
    colVector[2] = 0.1;
    shapes[currShape++] = new Triangle(v1, v2, v3, colVector);

    //4 TRIG WINDOW
    v1[0] = 0.3;
    v1[1] = 0.05;
    v2[0] = 0.3;
    v2[1] = 0.20;
    v3[0] = 0.5;
    v3[1] = 0.05;
    colVector[0] = 0.1;
    colVector[1] = 0.1;
    colVector[2] = 0.9;
    shapes[currShape++] = new Triangle(v1, v2, v3, colVector);

    //5 RECT WINDOW
    v1[0] = -0.3;
    v1[1] = 0.2;
    v2[0] = 0;
    v2[1] = 0.2;
    v3[0] = -0.3;
    v3[1] = 0.05;
    v4[0] = 0;
    v4[1] = 0.05;
    colVector[0] = 0.1;
    colVector[1] = 0.1;
    colVector[2] = 0.9;
    shapes[currShape++] = new Rectangle(v1, v2, v3, v4, colVector);

    //6 LEFT WHEEL
    colVector[0] = 0.1;
    colVector[1] = 0.1;
    colVector[2] = 0.1;
    shapes[currShape++] = new Circle(60, 0.15, -0.3, -0.5, colVector);

    //7 LEFT RIM
    colVector[0] = 0.4;
    colVector[1] = 0.4;
    colVector[2] = 0.4;
    shapes[currShape++] = new Circle(8, 0.1, -0.3, -0.5, colVector);

    //8 RIGHT WHEEL
    colVector[0] = 0.1;
    colVector[1] = 0.1;
    colVector[2] = 0.1;
    shapes[currShape++] = new Circle(60, 0.15, 0.3, -0.5, colVector);

    //9 RIGHT RIM
    colVector[0] = 0.4;
    colVector[1] = 0.4;
    colVector[2] = 0.4;
    shapes[currShape++] = new Circle(8, 0.1, 0.3, -0.5, colVector);

}

Box::Box(Vector center, double height, double width, double length, Vector color){
    double* arr;
    
    arr = new double[3];
    arr[0] = 0; arr[1] = height / 2; arr[2] = 0;
    Vector topPlane = center + Vector(3, arr);
    
    arr = new double[3];
    arr[0] = 0; arr[1] = height / 2; arr[2] = 0;
    Vector bottomPlane = center - Vector(3, arr);
    
    arr = new double [3];
    arr[0] = width / 2; arr[1] = arr[2] = 0;
    Vector leftPlane = center - Vector(3, arr);

    arr = new double [3];
    arr[0] = width / 2; arr[1] = arr[2] = 0;
    Vector rightPlane = center + Vector(3, arr);

    arr = new double [3];
    arr[0] = arr[1] = 0; arr[2] = length / 2;
    Vector nearPlane = center - Vector(3, arr);

    arr = new double [3];
    arr[0] = arr[1] = 0; arr[2] = length / 2;
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
Boxes::Boxes(int numBoxes, Vector* centers, double* heights, double* widths, double* lengths, Vector* colors){
    numShapes = numBoxes;
    shapes = new Shape*[numShapes];
    for(int i=0; i < numShapes; i++){
        shapes[i] = new Box(centers[i],heights[i], widths[i], lengths[i], colors[i]);
    }
}