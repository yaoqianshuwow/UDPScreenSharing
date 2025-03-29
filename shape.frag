#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCord;
uniform sampler2D texturecamer;

void main(){
    FragColor =texture(texturecamer,TexCord);
}
