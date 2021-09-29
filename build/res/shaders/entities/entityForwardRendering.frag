#version 450

struct AmbientLight {
    vec4 color;
};

struct DirectionalLight {
    vec4 color;
    vec3 direction;
};

struct Material {
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

const int samples = 3;
const float samplesPerPixel = (samples * 2.0 + 1.0) * (samples * 2.0 + 1.0);

in vec4 worldPosition;
in vec3 passNormal;
in vec3 toCameraVector;
//in vec4 shadowCoords;

uniform AmbientLight ambient;
uniform DirectionalLight sun;
uniform Material material;

uniform vec3 cameraPosition;
//uniform sampler2D shadowMap;
//uniform vec2 shadowMapSize;

out vec4 outColor;

vec4 computeAmbientColor() {
    return material.diffuse * ambient.color;
}

vec4 computeSunColor() {

    // Diffuse
    vec3 normalDirection = normalize(passNormal);
    vec3 lightDirection = normalize(sun.direction);

    float brightness = clamp(dot(lightDirection, normalDirection), 0.0, 1.0);

    vec4 diffuse = material.diffuse * sun.color * brightness;

    // Specular
    vec3 position = worldPosition.xyz;
    vec3 reflectionVector = 2 * dot(lightDirection, normalDirection) * normalDirection - lightDirection;

    vec4 specular = material.specular * sun.color * clamp(pow(dot(reflectionVector, toCameraVector), material.shininess), 0.0, 1.0);

    return diffuse + specular;
}

void main() {
    vec4 ambientColor = computeAmbientColor();
    vec4 sunColor = computeSunColor();

//    float horizontalPixelSize = 1.0 / shadowMapSize.x;
//    float verticalPixelSize = 1.0 / shadowMapSize.y;
//
//    float shadowValue = 0.0;
//
//    for (int x = -samples; x < samples; x++) {
//        for (int y = -samples; y < samples; y++) {
//            float distanceFromLight = texture(shadowMap, shadowCoords.xy + vec2(x * horizontalPixelSize, y * verticalPixelSize)).r;
//            float actualDistance = shadowCoords.z;
//            if (actualDistance - 0.0002 > distanceFromLight) {
//                shadowValue += 1.0;
//            }
//        }
//    }
//
//    shadowValue /= samplesPerPixel;
//    float lightFactor = 1.0 - (shadowValue * shadowCoords.w);

    outColor = ambientColor;
//    outColor += sunColor;
//    sunColor.rgb;
//    outColor.rgb += sunColor.rgb * lightFactor;
    outColor.rgb += sunColor.rgb;
//    outColor.rgb = abs(passNormal);
    outColor = clamp(outColor, 0.0, 1.0);
}