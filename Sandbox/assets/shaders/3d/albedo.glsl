#type VERTEX

#version 330 core
layout (location = 0) in vec3 in_Pos;
layout (location = 1) in vec4 in_Albedo;

out vec4 pass_Albedo;

uniform mat4 u_ProjectionViewMatrix;
uniform mat4 u_ModelMatrix;

void main()
{
    pass_Albedo = in_Albedo;
    gl_Position = u_ProjectionViewMatrix * u_ModelMatrix * vec4(in_Pos, 1.0);
}

#type FRAGMENT

#version 330 core

in vec4 pass_Albedo;

out vec4 out_FragColor;

void main()
{
    out_FragColor = pass_Albedo;
}
