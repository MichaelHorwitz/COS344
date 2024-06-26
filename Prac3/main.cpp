#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.hpp"
#include "shapes.h"

#define timeDT std::chrono::_V2::steady_clock::time_point

using namespace glm;
using namespace std;

const char *getError()
{
    const char *errorDescription;
    glfwGetError(&errorDescription);
    return errorDescription;
}

inline void startUpGLFW()
{
    glewExperimental = true; // Needed for core profile
    if (!glfwInit())
    {
        throw getError();
    }
}

inline void startUpGLEW()
{
    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        throw getError();
    }
}

inline GLFWwindow *setUp()
{
    startUpGLFW();
    glfwWindowHint(GLFW_SAMPLES, 4);               // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
    GLFWwindow *window;                                            // (In the accompanying source code, this variable is global for simplicity)
    window = glfwCreateWindow(1000, 1000, "Experiment", NULL, NULL);
    if (window == NULL)
    {
        cout << getError() << endl;
        glfwTerminate();
        throw "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n";
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    startUpGLEW();
    return window;
}

int main()
{
    //Standard
    GLFWwindow *window;
    try
    {
        window = setUp();
    }
    catch (const char *e)
    {
        cout << e << endl;
        throw;
    }

    glClearColor(0.1, 0.1, 0.2, 0.2);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_NEAREST);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    GLuint programID = LoadShaders("vertexShader.glsl", "fragmentShader.glsl");

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);

    Vector *centers = new Vector[2];

    double * arr = new double[3];
    arr[0] = arr[1] = arr[2] = 0;
    centers[0] = Vector(3, arr);
    
    arr = new double[3];
    arr[0] = arr[1] = arr[2] = -0.1;
    centers[1] = Vector(3, arr);

    double heights[2] = {
        0.2,
        0.2,
    };
    double widths[2] = {
        0.2,
        0.2,
    };
    double lengths[2] = {
        0.2,
        0.2,
    };

    Vector* colors = new Vector[2];
    arr = new double[3];
    arr[0] = arr[1] = 0; arr[2] = 1;
    colors[0] = Vector(3, arr);
    arr = new double[3];
    arr[0] = 1; arr[1] = arr[2] = 0;
    colors[1] = Vector(3, arr);

    Shape *shp = new Boxes(2, centers, heights, widths, lengths, colors);
    shp->toColorArray();
    bool firstRun = true;
    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        GLfloat *vertices = shp->toVertexArray();
        GLfloat *colors = shp->toColorArray();

        //Bind VBOS
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[shp->numVertices()]), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[shp->numColors()]), colors, GL_STATIC_DRAW);

        //VAO things
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *)0
        );

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *)0
        );
        glDrawArrays(GL_TRIANGLES, 0, shp->numVertices());

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        //Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        {
            //mat4x4 rotationX = mat4x4(0.0f);
            double** matArr = new double * [4];
            for (size_t i = 0; i < 4; i++)
            {
                matArr[i] = new double[4];
                for (size_t j = 0; j < 4; j++)
                {
                    matArr[i][j] = 0.0f;
                }
                
            }
            Matrix rotationX = Matrix(4, 4, matArr);
            rotationX[0][0] = 1;
            rotationX[1][1] = cos(0.02);
            rotationX[1][2] = -sin(0.02);
            rotationX[2][1] = sin(0.02);
            rotationX[2][2] = cos(0.02);
            rotationX[3][3] = 1;

            //mat4x4 rotationY = mat4x4(0.0f);
            matArr = new double * [4];
            for (size_t i = 0; i < 4; i++)
            {
                matArr[i] = new double[4];
                for (size_t j = 0; j < 4; j++)
                {
                    matArr[i][j] = 0.0f;
                }
                
            }
            Matrix rotationY = Matrix(4, 4, matArr);

            rotationY[0][0] = cos(0.04);
            rotationY[0][2] = -sin(0.04);
            rotationY[1][1] = 1;
            rotationY[2][0] = sin(0.04);
            rotationY[2][2] = cos(0.04);
            rotationY[3][3] = 1;

            Matrix rot = rotationX * rotationY;

            shp->applyMatrix(rot);
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            //mat4x4 rotationX = mat4x4(0.0f);
            double** matArr = new double * [4];
            for (size_t i = 0; i < 4; i++)
            {
                matArr[i] = new double[4];
                for (size_t j = 0; j < 4; j++)
                {
                    matArr[i][j] = 0.0f;
                }
                
            }
            Matrix rotationX = Matrix(4, 4, matArr);
            rotationX[0][0] = 1;
            rotationX[1][1] = cos(-0.02);
            rotationX[1][2] = -sin(-0.02);
            rotationX[2][1] = sin(-0.02);
            rotationX[2][2] = cos(-0.02);
            rotationX[3][3] = 1;

            //mat4x4 rotationY = mat4x4(0.0f);
            matArr = new double * [4];
            for (size_t i = 0; i < 4; i++)
            {
                matArr[i] = new double[4];
                for (size_t j = 0; j < 4; j++)
                {
                    matArr[i][j] = 0.0f;
                }
                
            }
            Matrix rotationY = Matrix(4, 4, matArr);

            rotationY[0][0] = cos(-0.04);
            rotationY[0][2] = -sin(-0.04);
            rotationY[1][1] = 1;
            rotationY[2][0] = sin(-0.04);
            rotationY[2][2] = cos(-0.04);
            rotationY[3][3] = 1;

            Matrix rot = rotationX * rotationY;

            shp->applyMatrix(rot);
        }

        delete[] vertices;
        delete[] colors;
        firstRun = false;
        
    } while (glfwGetKey(window, GLFW_KEY_SPACE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);
             

    //delete shp;
}
