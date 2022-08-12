#version 400

layout (location=0) in vec3 vPosition;
layout (location=1) in vec3 vNormal;
layout (location=2) in vec2 vTex;

uniform mat4 worldTransform;
uniform mat4 viewProjection;
//uniform mat4 proj;

out vec2 texCoor;
// Normal and position of vertex in world space
out vec3 vertexNormal;
out vec3 vertexPosition;

void main(void) 
{
    vec4 pos = worldTransform * vec4(vPosition, 1.0);

    vertexPosition = pos.xyz;
    vertexNormal = (worldTransform * vec4(vNormal, 0.0)).xyz;

    gl_Position = viewProjection* pos;

    texCoor = vTex;
}