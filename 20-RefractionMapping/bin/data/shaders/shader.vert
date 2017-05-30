#version 150
precision mediump float;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 mvp;

in vec3 position;
in vec3 normal;
in vec4 color;
in vec2 texcoord;

out vec3 vPosition;
out vec3 vNormal;
out vec3 envBoxvNormal;
out vec4 vColor;
out vec2 vTexCoord;

void main() {
    vPosition      = (model * vec4(position, 1.0)).xyz;
    vNormal        = normalize((model * vec4(normal, 0.0)).xyz);
    envBoxvNormal  = position;
    vColor         = color;
    gl_Position    = mvp * vec4(position, 1.0);
}
