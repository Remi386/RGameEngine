#version 400

in vec2 texCoor;

uniform mat4 worldTransform;
uniform mat4 viewProjection;

uniform sampler2D mTexture;

out vec4 color;

void main(void) {
    color = texture(mTexture, texCoor);
}
