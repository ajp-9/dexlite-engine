#type VERTEX

#version 410 core

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Color;

out vec3 pass_Color;

uniform mat4 u_ProjectionViewMatrix;

void main()
{
    pass_Color = in_Color;

    gl_Position = u_ProjectionViewMatrix * vec4(in_Position, 1.0);
}

#type FRAGMENT

#version 410 core

layout(location = 0) out vec4 out_Color;

in vec3 pass_Color;

void main()
{
    out_Color = vec4(pass_Color, 1.0);
}
