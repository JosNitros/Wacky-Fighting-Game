#version 330 core

in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D scene;

uniform mat2 frameM;
uniform float frame;

void main()
{
    vec2 ncoords = texCoords * frameM;
    vec2 trans = vec2(ncoords.x + frame, ncoords.y);
    FragColor = texture(scene, trans);
} 