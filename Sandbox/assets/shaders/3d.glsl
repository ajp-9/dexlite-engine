#type VERTEX

#version 330 core
layout (location = 0) in vec3 in_Pos;

uniform mat4 u_ProjectionViewMatrix;
uniform mat4 u_ModelMatrix;

void main()
{
    gl_Position = u_ProjectionViewMatrix * u_ModelMatrix * vec4(in_Pos, 1.0);
}

#type FRAGMENT

#version 330 core

out vec4 out_FragColor;

void main()
{
    out_FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
}
