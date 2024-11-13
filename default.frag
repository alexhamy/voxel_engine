#version 330 core
out vec4 FragColor;

uniform vec3 color;  // Add this line to accept the color uniform

void main()
{
    FragColor = vec4(color, 1.0);  // Use the color uniform as the block color
}
