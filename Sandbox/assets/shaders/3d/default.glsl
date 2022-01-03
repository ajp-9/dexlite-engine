#type VERTEX

#version 330 core

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;
layout (location = 2) in vec4 in_Color;
layout (location = 3) in vec2 in_TexCoord;
layout (location = 4) in float in_Roughness;

out vec3 pass_Normal;
out vec4 pass_Color;
out vec2 pass_TexCoord;
out vec3 pass_FragPosition;
out float pass_Roughness;

uniform mat4 u_ProjectionViewMatrix;
uniform mat4 u_ModelMatrix;
uniform mat3 u_InverseModelMatrix;

void main()
{
    pass_Normal = normalize(u_InverseModelMatrix * in_Normal);
    pass_Color = in_Color;
    pass_TexCoord = in_TexCoord;
    pass_FragPosition = vec3(u_ModelMatrix * vec4(in_Position, 1.0));
    pass_Roughness = in_Roughness;

    gl_Position = u_ProjectionViewMatrix * u_ModelMatrix * vec4(in_Position, 1.0);
}

#type FRAGMENT

#version 330 core

out vec4 out_Color;

in vec3 pass_Normal;
in vec4 pass_Color;
in vec2 pass_TexCoord;
in vec3 pass_FragPosition;
in float pass_Roughness;

struct Material
{
    float TexTilingFactor;

    bool BaseColorTextureEnabled;
    sampler2D BaseColorTextureSampler;
    
    bool RoughnessTextureEnabled;
    sampler2D RoughnessTextureSampler;

    bool EmissiveTextureEnabled;
    sampler2D EmissiveTextureSampler;
};

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

uniform Material u_Material;

uniform vec3 u_CameraPosition;

uniform AmbientLight u_AmbientLight;
uniform DirectionalLight u_DirectionalLight;

vec3 CalcDirLight();

vec3 shimmer = vec3(0.0);
float frag_shininess = 1.0 - pass_Roughness;
vec3 view_dir = normalize(u_CameraPosition - pass_FragPosition);

void main()
{
    vec4 base_color = pass_Color;

    if (u_Material.BaseColorTextureEnabled)
    {
        base_color *= texture(u_Material.BaseColorTextureSampler, pass_TexCoord * u_Material.TexTilingFactor);
        
        if (base_color.a == 0.0)
            discard;
    }

    if (u_Material.RoughnessTextureEnabled)
        frag_shininess += 1.0 - texture(u_Material.RoughnessTextureSampler, pass_TexCoord * u_Material.TexTilingFactor).g;

    vec3 light_color = vec3(0.0);

    if (u_AmbientLight.Enabled)
        light_color += u_AmbientLight.Color;

    if (u_DirectionalLight.Enabled)
        light_color += CalcDirLight();
    
    if (!u_Material.EmissiveTextureEnabled)
        out_Color = (base_color * vec4(light_color, 1.0)) + vec4(shimmer, 0.0);
    else
        out_Color = (base_color * vec4(light_color, 1.0)) + vec4(shimmer, 0.0) + vec4(texture(u_Material.EmissiveTextureSampler, pass_TexCoord * u_Material.TexTilingFactor).rgb, 0.0);
}

vec3 CalcDirLight()
{
    vec3 lightDir = normalize(-u_DirectionalLight.Direction);
    float brightness = max(dot(pass_Normal, lightDir), 0);

    vec3 reflectDir = reflect(-lightDir, pass_Normal);
    shimmer = u_DirectionalLight.Color * pow(max(dot(view_dir, reflectDir), 0.0), 256) * frag_shininess;

    return u_DirectionalLight.Color * brightness;
}
