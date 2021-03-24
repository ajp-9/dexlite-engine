#type VERTEX

#version 330

layout (location = 0) in vec3 aPos;

void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
};

#type FRAGMENT

#version 330

out vec4 FragColor;

void main()
{
    FragColor = vec4(0.0f, 0.0f);
}