#type VERTEX

#version 330 core
layout (location = 0) in vec3 in_Pos;
layout (location = 1) in vec3 in_Normal;
layout (location = 2) in vec2 in_TexCoord;

out vec2 pass_TexCoord;
out float pass_test1;
out float pass_test2;

uniform mat4 u_ProjectionViewMatrix;
uniform mat4 u_ModelMatrix;

struct Data
{
    int b;
    vec3 w;
    mat4 mm;
    vec2 w1;
    int what;
    vec3 w2;
    float values;
};

layout (std140) uniform ubo_ProjectionViewMatrix
{
    Data dat[2];
};

layout (std140) uniform ubo_ModelMatrix
{
    mat4 modelMatrix;
};

void main()
{
    pass_TexCoord = in_TexCoord;
    pass_test1 = dat[0].values;
    pass_test2 = dat[1].values;

    gl_Position = u_ProjectionViewMatrix * u_ModelMatrix * vec4(in_Pos, 1.0);
}

#type FRAGMENT

#version 330 core

in vec2 pass_TexCoord;
in float pass_test1;
in float pass_test2;

out vec4 out_FragColor;

uniform sampler2D u_TextureSampler;

void main()
{
    out_FragColor = vec4(pass_test1, pass_test2, pass_test1, 1);
}
