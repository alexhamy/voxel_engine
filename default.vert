#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; // Vertex color input

out vec3 fragmentColor; // Pass color to fragment shader

uniform mat4 camMatrix;
uniform mat4 model;

void main() {
    gl_Position = camMatrix * model * vec4(aPos, 1.0);
    fragmentColor = aColor; // Pass the vertex color to the fragment shader
}
