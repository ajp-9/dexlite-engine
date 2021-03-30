#type VERTEX

#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vColor;

out vec3 color;

uniform mat4 u_ProjectionViewMatrix;
uniform mat4 u_ModelMatrix;

void main()
{
    color = vColor;
    gl_Position = u_ProjectionViewMatrix * u_ModelMatrix * vec4(vPos, 1.0);
}

#type FRAGMENT

#version 330 core

in vec3 color;

out vec4 FragColor;

void main()
{
    FragColor = vec4(color, 1.0f);
}
