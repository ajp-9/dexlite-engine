#type VERTEX

#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in float vColor;

out float color;

uniform mat4 u_ProjectionViewMatrix;

void main()
{
    color = vColor;
    gl_Position = u_ProjectionViewMatrix * vec4(vPos, 1.0);
}

#type FRAGMENT

#version 330

in float color;

out vec4 FragColor;

void main()
{
    FragColor = vec4(color, color, color, 1.0f);
}
