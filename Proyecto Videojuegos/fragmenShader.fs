#version 330 core
out vec4 FragColor;

in vec2 ourTexture1;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, ourTexture1);
}