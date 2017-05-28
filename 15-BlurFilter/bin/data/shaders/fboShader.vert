#version 150
precision mediump float;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 mvp;
uniform mat4 inv;
uniform vec3 lightDirection;

in vec2 texcoord;
in vec3 position;
in vec3 normal;
in vec4 color;

out vec2 vTextureCoord;
out vec4 vColor;

void main() {
    vTextureCoord = texcoord;
//    vec3  invLight = normalize(inv * vec4(lightDirection, 0.0)).xyz;
//    float diffuse  = clamp(dot(normal, invLight), 0.1, 1.0);
//    vColor = color * vec4(vec3(diffuse), 1.0);
    vColor = color;
    //gl_Position = projection * view * model * vec4(position, 1.0);
    gl_Position = mvp * vec4(position, 1.0);
}
