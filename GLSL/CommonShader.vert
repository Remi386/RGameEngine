#version 400

layout (location=0) in vec3 position;

uniform mat4 worldTransform;
uniform mat4 view;
uniform mat4 proj;

out vec4 mColor;

void main(void) 
{
    vec4 pos = vec4(position, 1.0);
    gl_Position = proj * view * worldTransform * pos;
    mColor = pos * 0.2 + vec4(0.5, 0.5, 0.5, 0.5);
}