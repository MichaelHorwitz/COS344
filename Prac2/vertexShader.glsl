#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec2 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
out vec3 fragmentColor;
uniform mat3 transformationMatrix;

void main(){
    vec3 pos = vec3(vertexPosition_modelspace, 1.0);
    vec3 newPos = transformationMatrix * pos;
    mat3 ident = mat3(1.0);
    gl_Position.xy = newPos.xy;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;
    fragmentColor = vertexColor;

}

