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
    window = glfwCreateWindow(1000, 1000, "u22512323", NULL, NULL);
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
    std::cout << "How many rectangles for the backsheet?" << std::endl;
    int numRectangles;
    std::cin >> numRectangles;
    GLFWwindow *window;
    try
    {
        window = setUp();
    }
    catch (const char *e)
    {
        std::cout << e << std::endl;
        throw;
    }

    Vector4 colors[10] = {
        Vector4(1.0f, 0.0f, 0.0f, 1.0f),
        Vector4(0.0f, 1.0f, 0.0f, 1.0f),
        Vector4(0.0f, 0.0f, 1.0f, 1.0f),
        Vector4(1.0f, 1.0f, 1.0f, 1.0f),
        Vector4(0.0f, 0.0f, 0.0f, 1.0f),
        Vector4(1.0f, 1.0f, 0.0f, 1.0f),
        Vector4(0.0f, 1.0f, 1.0f, 1.0f),
        Vector4(1.0f, 0.0f, 1.0f, 1.0f),
        Vector4(0.7f, 0.5f, 0.3f, 1.0f),
        Vector4(0.3f, 0.5f, 0.7f, 1.0f),
    };
    int currBackCol = 0;
    int currGlassCol = 0;
    float currOpacity = 0.5f;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    GLuint programID = LoadShaders("vertexShader.glsl", "fragmentShader.glsl");

    unsigned int VBO, VAO, CBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &CBO);

    Shape * shape = new Shape();
    Shape * backSheet = new BackSheet(
        Vector3(0.9f, 0.8f, 0.5f),
        Vector3(-0.9f, 0.8f, 0.5f),
        Vector3(-0.9f,  -0.8f, 0.5f), 
        Vector3(0.9f,  -0.80f, 0.5f), 
        Vector4(1.0f,0.0f,0.0f,1.0f), 
        Vector4(0.0f,1.0f,0.0f,1.0f), 
        numRectangles
    );
    Shape * glass = new Cuboid(
        Vector3(0.9f,   0.8f,   0.25f),
        Vector3(-0.9f,  0.8f,   0.25f),
        Vector3(-0.9f,  -0.8f,  0.25f), 
        Vector3(0.9f,   -0.80f, 0.25f), 
        0.1f,
        Vector4(0.0f,0.0f,1.0f,0.5f)
    );
    shape = shape->addShape(backSheet);
    shape = shape->addShape(glass);
    
    std::cout << shape->numVertices() << std::endl;
    std::cout << shape->toVertexArray() << std::endl;
    float* arr = shape->toVertexArray();
    for (int i = 0; i < shape->numVertices(); i++)
    {
        if (i % 3 == 0)
        {
            std::cout << std::endl;
        }
        std::cout << arr[i] << ", ";
        
        
    }
    std::cout << std::endl;
    std::cout << shape->numColors() << std::endl;
    std::cout << shape->toColorArray() << std::endl;
    float* arr2 = shape->toColorArray();
    for (int i = 0; i < shape->numColors(); i++)
    {
        if (i % 4 == 0)
        {
            std::cout << std::endl;
        }
        std::cout << arr2[i] << ", ";
    }
    std::cout << std::endl;
    // Main loop
    while(!glfwWindowShouldClose(window))
    {
        // Input handling
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
            glfwSetWindowShouldClose(window, true);
        }
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        {
            if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
            {
                backSheet->changeColor(colors[++currBackCol % 10]);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        {
            if (glfwGetKey(window, GLFW_KEY_O) == GLFW_RELEASE)
            {
                backSheet->changeColor(colors[--currBackCol % 10]);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        {
            if (glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE)
            {
                Vector4 temp = colors[++currGlassCol % 10];
                temp[3] = currOpacity;
                glass->changeColor(temp);
            }
        }   
        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        {
            if (glfwGetKey(window, GLFW_KEY_K) == GLFW_RELEASE)
            {
                Vector4 temp = colors[++currGlassCol % 10];
                temp[3] = currOpacity;
                glass->changeColor(temp);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        {
            if (glfwGetKey(window, GLFW_KEY_M) == GLFW_RELEASE)
            {
                Vector4 temp = colors[currGlassCol % 10];
                currOpacity += 0.1f;
                if (currOpacity > 1.0f)
                {
                    currOpacity = 1.0f;
                }
                
                temp[3] = currOpacity;
                glass->changeColor(temp);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        {
            if (glfwGetKey(window, GLFW_KEY_N) == GLFW_RELEASE)
            {
                Vector4 temp = colors[currGlassCol % 10];
                currOpacity -= 0.1f;
                if (currOpacity < 0.0f)
                {
                    currOpacity = 0.0f;
                }
                
                temp[3] = currOpacity;
                glass->changeColor(temp);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            float angle = M_PI / 80;
            float cosAngle = cos(angle);
            float sinAngle = sin(angle);
            double rotationMatrixDoubles[4][4] = {
                {1, 0, 0, 0},
                {0, cosAngle, -sinAngle, 0},
                {0, sinAngle, cosAngle, 0},
                {0, 0, 0, 1}
            };
            double ** temp = new double*[4];
            for (int i = 0; i < 4; i++)
            {
                temp[i] = new double[4];
                for (int j = 0; j < 4; j++)
                {
                    temp[i][j] = rotationMatrixDoubles[i][j];
                }
            }
            Matrix4x4 rotationMatrix;
            Matrix tempMatrix = Matrix(4, 4, temp);
            rotationMatrix = rotationMatrix.convertTo4x4(tempMatrix);
            shape->applyMatrix(rotationMatrix);

        }

        // OpenGl rendering
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[shape->numVertices()]), shape->toVertexArray(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, CBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[shape->numColors()]), shape->toColorArray(), GL_STATIC_DRAW);
    
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glUseProgram(programID);
        glBindVertexArray(VAO); 
        glDrawArrays(GL_TRIANGLES, 0, shape->numVertices());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(programID);

    glfwTerminate();
    return 0;
}
