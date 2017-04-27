#version 150
precision mediump float;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 mvp;
uniform float vertexAlpha;

in vec2 texcoord;
in vec3 position;
in vec4 color;

out vec2 vTextureCoord;
out vec4 vColor;

void main() {
    vTextureCoord = texcoord;
    vColor = vec4(color.rgb, color.a * vertexAlpha);
    //gl_Position = projection * view * model * vec4(position, 1.0);
    gl_PointSize = 32.0;
    gl_Position = mvp * vec4(position, 1.0);
}
