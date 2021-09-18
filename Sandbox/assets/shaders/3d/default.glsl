#type VERTEX

#version 330 core

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;
layout (location = 2) in vec4 in_Color;
layout (location = 3) in vec2 in_TexCoord;

out vec3 pass_Normal;
out vec4 pass_Color;
out vec2 pass_TexCoord;

uniform mat4 u_ProjectionViewMatrix;
uniform mat4 u_ModelMatrix;

void main()
{
    pass_Normal = in_Normal;
    pass_Color = in_Color;
    pass_TexCoord = in_TexCoord;

    gl_Position = u_ProjectionViewMatrix * u_ModelMatrix * vec4(in_Position, 1.0);
}

#type FRAGMENT

#version 330 core

out vec4 out_FragColor;

in vec3 pass_Normal;
in vec4 pass_Color;
in vec2 pass_TexCoord;

uniform float u_TexTilingFactor;

uniform sampler2D u_DiffuseMapSampler;
uniform bool u_DiffuseMapEnabled;

uniform sampler2D u_SpecularMapSampler;
uniform bool u_SpecularMapEnabled;

void main()
{
    vec4 fragColor = pass_Color;

    if (u_DiffuseMapEnabled)
        fragColor *= texture(u_DiffuseMapSampler, pass_TexCoord * u_TexTilingFactor);

    if (u_SpecularMapEnabled)
        fragColor *= texture(u_DiffuseMapSampler, pass_TexCoord * u_TexTilingFactor);

    out_FragColor = fragColor;
}
