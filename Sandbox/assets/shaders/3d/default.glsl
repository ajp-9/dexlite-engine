#type VERTEX

#version 330 core
layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;
layout (location = 2) in vec4 in_Color;
layout (location = 2) in vec2 in_TexCoord 
layout (location = 2)
layout (location = 2) 

				glm::vec3 position = glm::vec3(0),
				glm::vec3 normal = glm::vec3(0),
				glm::vec4 color = glm::vec4(0),
				glm::vec2 texCoord = glm::vec2(0),
				float texTilingFactor = 1.0f,
				float diffuseMapIndex = 0,
				float specularMapIndex = 0)

out vec2 pass_TexCoord;
out float pass_test1;
out float pass_test2;

uniform mat4 u_ProjectionViewMatrix;
uniform mat4 u_ModelMatrix;

layout (std140) uniform ubo_ProjectionViewMatrix
{
    mat4 ubo_ProjectionViewMatrix;
};

layout (std140) uniform ubo_ModelMatrix
{
    mat4 ubo_ModelMatrix;
};

void main()
{
    pass_TexCoord = in_TexCoord;

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
