#version 150
precision mediump float;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 mvp;
uniform int edge;

in vec3 position;
in vec3 normal;
in vec4 color;

out vec3 vPosition;
out vec3 vNormal;
out vec4 vColor;

void main() {
    vec3 pos = position;
    if(edge == 1){
        pos += normal * 1.5;
    }
    vNormal = normal;
    vColor = color;
    
    gl_Position = mvp * vec4(pos, 1.0);
}

