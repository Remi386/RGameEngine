#version 400

in vec4 mColor;

uniform mat4 worldTransform;
uniform mat4 viewProjection;

out vec4 color;

void main()
{
	color = mColor;
}