#version 150
precision mediump float;

uniform mat4 inv;
uniform vec3 lightPosition;
uniform vec3 eyeDirection;
uniform vec4 ambientColor;

in vec3 vPosition;
in vec3 vNormal;
in vec4 vColor;

out vec4 outputColor;

void main(){
    vec3  lightVec  = lightPosition - vPosition;
    vec3  invLight  = normalize(inv * vec4(lightVec, 0.0)).xyz;
    vec3  invEye    = normalize(inv * vec4(eyeDirection, 0.0)).xyz;
    vec3  halfLE    = normalize(invLight + invEye);
    float diffuse   = clamp(dot(vNormal, invLight), 0.0, 1.0) + 0.2;
    float specular  = pow(clamp(dot(vNormal, halfLE), 0.0, 1.0), 50.0);
    vec4  destColor = vColor * vec4(vec3(diffuse), 1.0) + vec4(vec3(specular), 1.0) + ambientColor;
    outputColor = destColor;
}
