#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main()
{
    vec3 tmpPos;
    tmpPos = vec3(aPos.x, -aPos.y, aPos.z);
    gl_Position = vec4(tmpPos, 1.0);
    ourColor = aColor;
}