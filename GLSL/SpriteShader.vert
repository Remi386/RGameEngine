#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tex;

uniform mat4 worldTransform;
uniform mat4 viewProjection;

out vec2 texCoor;

void main(void) 
{
    gl_Position = viewProjection * worldTransform * vec4(position, 1.0);
    texCoor = tex;
}