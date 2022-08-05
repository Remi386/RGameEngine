#version 400

in vec2 texCoor;
in vec3 vertexNormal;
in vec3 vertexPosition;

struct DirectLight
{
    vec3 lightDirection;
    vec3 diffuseColor;
    vec3 specularColor;
};

uniform vec3 cameraPosition;
uniform vec3 ambientLight;
uniform float specularPower;
uniform DirectLight dirLight;

uniform sampler2D mTexture;

out vec4 color;

void main(void) 
{
    vec3 n = normalize(vertexNormal);
    vec3 l = normalize(-dirLight.lightDirection);
    
    vec3 phong = ambientLight;
    float nl = dot(n, l);

    if (nl > 0) {
        vec3 v = normalize(cameraPosition - vertexPosition);
        vec3 r = normalize(reflect(-l, n));

        vec3 diffuse = dirLight.diffuseColor * nl;
        vec3 specular = dirLight.specularColor * pow(max(0.0, dot(r, v)), specularPower);
        phong += diffuse + specular;
    }

    color = texture(mTexture, texCoor) * vec4(phong, 1.0);
}
