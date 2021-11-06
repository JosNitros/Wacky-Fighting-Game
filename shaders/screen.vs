#version 330 core

layout (location = 0) in vec2 vertex;

out vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = projection * model * vec4(vertex.x, 1.0 - vertex.y, 0.0, 1.0);
    texCoords = vertex.xy;
}