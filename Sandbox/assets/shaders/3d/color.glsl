#type VERTEX

#version 330 core
layout (location = 0) in vec3 in_Pos;
layout (location = 1) in vec4 in_Diffuse;

out vec4 pass_Diffuse;

uniform mat4 u_ProjectionViewMatrix;
uniform mat4 u_ModelMatrix;

layout (std140) uniform ubo_ProjectionViewMatrix
{
    mat4 ubo_ProjectionViewMatrix;
};

layout (std140) uniform ubo_ModelMatrix
{
    mat4 modelMatrix;
};

void main()
{
    pass_Diffuse = in_Diffuse;
    gl_Position = ubo_ProjectionViewMatrix * u_ProjectionViewMatrix * u_ModelMatrix * vec4(in_Pos, 1.0);
}

#type FRAGMENT

#version 330 core

in vec4 pass_Diffuse;

out vec4 out_FragColor;

void main()
{
    out_FragColor = pass_Diffuse;
}
