#version 150
precision mediump float;

uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec4 color;
in vec2 texcoord;

out vec2 vTexCoord;
out vec4 vColor;
out vec4 vPosition;

void main() {
    vTexCoord = texcoord;
    vColor = color;
    vPosition = position;
    gl_Position = modelViewProjectionMatrix * position;
}
