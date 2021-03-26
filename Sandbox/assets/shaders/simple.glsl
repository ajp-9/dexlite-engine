#type VERTEX

#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in float vColor;

out float color;

void main()
{
    gl_Position = vec4(vPos, 1.0);
    color = vColor;
}

#type FRAGMENT

#version 330

in float color;

out vec4 FragColor;

void main()
{
    FragColor = vec4(color, color, color, 1.0f);
}
