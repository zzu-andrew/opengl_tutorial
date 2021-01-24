#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
// glBindTexture(GL_TEXTURE_2D, texture); 自动将纹理赋值给片段着色器
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
   // 在shader的fs文件中实现对texture的x轴镜像
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
}