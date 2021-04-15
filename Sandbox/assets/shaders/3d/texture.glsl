#type VERTEX

#version 330 core
layout (location = 0) in vec3 in_Pos;
layout (location = 1) in vec3 in_Normal;
layout (location = 2) in vec2 in_TexCoord;

out vec2 pass_TexCoord;

uniform mat4 u_ProjectionViewMatrix;
uniform mat4 u_ModelMatrix;

void main()
{
    pass_TexCoord = in_TexCoord;
    gl_Position = u_ProjectionViewMatrix * u_ModelMatrix * vec4(in_Pos, 1.0);
}

#type FRAGMENT

#version 330 core

in vec2 pass_TexCoord;

out vec4 out_FragColor;

uniform sampler2D u_TextureSampler;

void main()
{
    out_FragColor = texture(u_TextureSampler, pass_TexCoord);
}
