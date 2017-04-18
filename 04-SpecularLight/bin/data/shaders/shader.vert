#version 150
precision mediump float;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 mvp;
uniform mat4 inv;
uniform vec3 lightDirection;
uniform vec3 eyeDirection;
uniform vec4 ambientColor;

in vec3 position;
in vec3 normal;
in vec4 color;

out vec4 vColor;

void main() {
    vec3  invLight = normalize(inv * vec4(lightDirection, 0.0)).xyz;
    vec3  invEye   = normalize(inv * vec4(eyeDirection, 0.0)).xyz;
    vec3  halfLE   = normalize(invLight + invEye);
    float diffuse  = clamp(dot(normal, invLight), 0.1, 1.0);
    float specular = pow(clamp(dot(normal, halfLE), 0.0, 1.0), 50.0);
    vec4  light    = color * vec4(vec3(diffuse), 1.0) + vec4(vec3(specular), 1.0);
    vColor = light + ambientColor;
    //gl_Position = projection * view * model * vec4(position, 1.0);
    gl_Position = mvp * vec4(position, 1.0);
}
