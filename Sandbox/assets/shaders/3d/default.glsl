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
uniform mat3 u_InverseModelMatrix;

void main()
{
    pass_Normal = normalize(u_InverseModelMatrix * in_Normal);
    //pass_Normal = vec3(u_ModelMatrix * vec4(in_Normal, 0));
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

struct AmbientLight
{
    bool Enabled;
    vec3 Color;
};

struct DirectionalLight
{   
    bool Enabled;
    vec3 Color;
    vec3 Direction;
};

uniform AmbientLight u_AmbientLight;
uniform DirectionalLight u_DirectionalLight;

uniform float u_TexTilingFactor;

uniform sampler2D u_DiffuseMapSampler;
uniform bool u_DiffuseMapEnabled;

uniform sampler2D u_SpecularMapSampler;
uniform bool u_SpecularMapEnabled;

vec3 CalcDirLight(DirectionalLight light, vec3 normal);

void main()
{
    vec4 fragColor = pass_Color;

    if (u_DiffuseMapEnabled)
        fragColor *= texture(u_DiffuseMapSampler, pass_TexCoord * u_TexTilingFactor);

    //if (u_SpecularMapEnabled)
    //    fragColor *= texture(u_DiffuseMapSampler, pass_TexCoord * u_TexTilingFactor);

    vec4 light_color = vec4(1.0f);

    if (u_AmbientLight.Enabled)
        light_color *= vec4(u_AmbientLight.Color, 1.0f);

    if (u_DirectionalLight.Enabled)
        light_color *= vec4(CalcDirLight(u_DirectionalLight, pass_Normal), 1.0f);

    //out_FragColor = vec4(pass_Normal, 1.0);
    out_FragColor = light_color * fragColor;
}

vec3 CalcDirLight(DirectionalLight light, vec3 normal)
{
    vec3 lightDir = normalize(-light.Direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), u_AmbientLight.Color.x);
    // combine results
    vec3 diffuse = light.Color * diff/* * vec3(texture(material.diffuse, TexCoords))*/;
    //vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (diffuse);
}
