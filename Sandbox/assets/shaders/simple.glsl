#type VERTEX

#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 vTexCoord;

out vec3 color;
out vec2 texCoord;

uniform mat4 u_ProjectionViewMatrix;
uniform mat4 u_ModelMatrix;

void main()
{
    color = vColor;
    texCoord = vTexCoord;
    gl_Position = u_ProjectionViewMatrix * u_ModelMatrix * vec4(vPos, 1.0);
}

#type FRAGMENT

#version 330 core

in vec3 color;
in vec2 texCoord;

out vec4 FragColor;

void main()
{
    FragColor = vec4(color, 1.0f);
}
