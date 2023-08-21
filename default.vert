#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;  // Texture Coordinates

out vec3 vertexColor;
out vec2 texCoord;  // Pass texture coordinates to fragment shader

uniform mat4 modelMatrix;
uniform mat4 camMatrix;
uniform mat4 perspectiveMatrix;

void main()
{
    gl_Position = perspectiveMatrix * camMatrix * modelMatrix * vec4(aPos, 1.0);
    vertexColor = aColor;
    texCoord = aTexCoord;  // Pass texture coordinates to fragment shader
}
