#version 330 core

in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D scene;

void main()
{
    float dm = 1.7 - distance(gl_FragCoord.xy / 1280.0, vec2(0.5)) * 2.0;
    vec4 vig = vec4(dm, dm, dm, 1.0);
    FragColor = texture(scene, texCoords) * vig;
}