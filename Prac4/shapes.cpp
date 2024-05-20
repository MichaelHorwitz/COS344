#include "shapes.h"

Shape::~Shape()
{

}

Shape::Shape()
{
    vertices = new Vector3 *[0];
    colors = new Vector4 *[0];
    shapes = new Shape *[0];
    numShapes = 0;
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
        for (int i = 0; i < numVertices() / 3; i++)
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
        for (int i = 0; i < numVertices() / 3; i++)
        {
            result[count++] = colors[i]->operator[](0);
            result[count++] = colors[i]->operator[](1);
            result[count++] = colors[i]->operator[](2);
            result[count++] = colors[i]->operator[](3);
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
            Vector4 tempV4 = Vector4((*vertices[i]), 1);
            Matrix tempMat = tempV4;
            Matrix resultMatrix = m * tempMat;
            Vector tempV = *(resultMatrix.toVector());
            Vector3 tempV3 = Vector3(tempV);
            (*vertices[i]) = tempV3;
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

Shape* Shape::addShape(Shape* shape)
{   
    Shape* newShape = new Shape();
    newShape->numShapes = 2;
    newShape->shapes = new Shape*[2];
    newShape->shapes[0] = this;
    newShape->shapes[1] = shape;
    return newShape;
}

void Shape::changeColor(Vector4 newColor)
{
    if (numShapes > 0)
    {
        for (int i = 0; i < numShapes; i++)
        {
            shapes[i]->changeColor(newColor);
        }
    } else {
        for (int i = 0; i < numPoints(); i++)
        {
            colors[i] = new Vector4(newColor);
        }
    }
    
}

Triangle::Triangle(Vector3 p1, Vector3 p2, Vector3 p3, Vector4 color)
{
    numShapes = 0;
    shapes = new Shape *[0];
    int n = 3;
    vertices = new Vector3 *[n];
    vertices[0] = new Vector3(p1);
    vertices[1] = new Vector3(p2);
    vertices[2] = new Vector3(p3);


    colors = new Vector4 * [n];
    for (int i = 0; i < n; i++)
    {
        colors[i] = new Vector4(color);
    }
}

int Triangle::numVertices()
{
    return 9;
}

int Triangle::numColors()
{
    return 12;
}

int Triangle::numPoints()
{
    return 3;
}

Rectangle::Rectangle(Vector3 ur, Vector3 ul, Vector3 ll, Vector3 lr, Vector4 color)
{
    numShapes = 2;
    shapes = new Shape *[numShapes];
    shapes[0] = new Triangle(ur, ul, ll, color);
    shapes[1] = new Triangle(ur, ll, lr, color);
    vertices = new Vector3 * [numPoints()];
    colors = new Vector4 * [numPoints()];
    int count = 0;
    for (int i = 0; i < numShapes; i++)
    {
        for (int j = 0; j < shapes[i]->numPoints(); j++)
        {
            vertices[count++] = shapes[i]->vertices[j];
        }
    }
    for (int i = 0; i < numPoints(); i++)
    {
        colors[i] = new Vector4(color);
    }
}

BackSheet::BackSheet(Vector3 ur, Vector3 ul, Vector3 ll, Vector3 lr, Vector4 color, Vector4 color2, int numRectangles)
{
    numShapes = numRectangles;
    shapes = new Shape *[numShapes];
    float width = abs(ur[0] - ul[0]);
    width = width / (numRectangles);
    std::cout << "Width: " << width << "\n";
    float l = ul[0];
    for (int i = 0; i < numShapes; i++)
    {
        std::cout << "l: " << l << "\n";
        float r = l + width;
        std::cout << "r: " << r << "\n";
        Vector3 newUR = Vector3(r, ur[1], ur[2]);
        Vector3 newUL = Vector3(l, ul[1], ul[2]);
        Vector3 newLL = Vector3(l, ll[1], ll[2]);
        Vector3 newLR = Vector3(r, lr[1], lr[2]);
        if (i % 2 == 0)
        {
            shapes[i] = new Rectangle(newUR, newUL, newLL, newLR, color);
            
        } else {
            shapes[i] = new Rectangle(newUR, newUL, newLL, newLR, color2);
        }
        l = l + width;
        
    }
    vertices = new Vector3 * [numPoints()];
    colors = new Vector4 * [numPoints()];
    int count = 0;
    for (int i = 0; i < numShapes; i++)
    {
        for (int j = 0; j < shapes[i]->numPoints(); j++)
        {
            vertices[count++] = shapes[i]->vertices[j];
        }
    }
    count = 0;
    for (int i = 0; i < numShapes; i++)
    {
        for (int j = 0; j < shapes[i]->numPoints(); j++)
        {
            colors[count++] = shapes[i]->colors[j];
        }
    }
}

BackSheet::BackSheet(Vector3 ur, Vector3 ul, Vector3 ll, Vector3 lr, Vector4 color, int numRectangles)
{
    BackSheet(ur, ul, ll, lr, color, color, numRectangles);
}

Cuboid::Cuboid(Vector3 ur, Vector3 ul, Vector3 ll, Vector3 lr, float depth, Vector4 color)
{
    numShapes = 6;
    shapes = new Shape *[numShapes];
    Vector3 ur2 = Vector3(ur[0], ur[1], ur[2] - depth);
    Vector3 ul2 = Vector3(ul[0], ul[1], ul[2] - depth);
    Vector3 ll2 = Vector3(ll[0], ll[1], ll[2] - depth);
    Vector3 lr2 = Vector3(lr[0], lr[1], lr[2] - depth);
    shapes[0] = new Rectangle(ur, ul, ll, lr, color);
    shapes[1] = new Rectangle(ur, ul, ul2, ur2, color);
    shapes[2] = new Rectangle(ur, ur2, lr2, lr, color);
    shapes[3] = new Rectangle(ul, ul2, ll2, ll, color);
    shapes[4] = new Rectangle(ll, ll2, lr2, lr, color);
    shapes[5] = new Rectangle(lr, lr2, ur2, ur, color);
    vertices = new Vector3 * [numPoints()];
    colors = new Vector4 * [numPoints()];
    int count = 0;
    for (int i = 0; i < numShapes; i++)
    {
        for (int j = 0; j < shapes[i]->numPoints(); j++)
        {
            vertices[count++] = shapes[i]->vertices[j];
        }
    }
    count = 0;
    for (int i = 0; i < numShapes; i++)
    {
        for (int j = 0; j < shapes[i]->numPoints(); j++)
        {
            colors[count++] = shapes[i]->colors[j];
        }
    }
}


