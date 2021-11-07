#version 330 core
out vec4 fragColor;

uniform vec4 color;

uniform float time;

void main()
{    
    fragColor = color;
    fragColor.x *= 0.125 * sin(time * 1.5) + 0.775;
}