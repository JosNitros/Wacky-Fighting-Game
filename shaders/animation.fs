#version 330 core

in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D scene;

uniform mat2 frameM;
uniform float frame;

uniform int flags;

void main()
{
    vec2 ncoords = texCoords * frameM;
    vec2 trans = vec2(ncoords.x + frame, ncoords.y);

    FragColor = texture(scene, trans);

    if ((flags & 1) > 0)
    {
        FragColor = vec4(1.0 - FragColor.x, 1.0 - FragColor.y, 1.0 - FragColor.z, FragColor.w);
    }

}