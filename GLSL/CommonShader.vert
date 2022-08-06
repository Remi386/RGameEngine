#version 400

layout (location=0) in vec3 position;
layout (location=1) in vec3 norm;
layout (location=2) in vec2 tex;

uniform mat4 worldTransform;
uniform mat4 viewProjection;

out vec2 texCoor;

void main(void) 
{
    vec4 pos = vec4(position, 1.0);
    gl_Position = viewProjection * worldTransform * pos;
    texCoor = tex;
}