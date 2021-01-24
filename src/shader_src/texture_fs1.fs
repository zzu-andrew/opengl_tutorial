#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
// glBindTexture(GL_TEXTURE_2D, texture); 自动将纹理赋值给片段着色器
uniform sampler2D texture1;

void main()
{
   // FragColor = texture(texture1, TexCoord);
	FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);
}