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
out vec3 envBoxvNormal;
out vec4 vColor;
out vec2 vTexCoord;
out vec3 tNormal;
out vec3 tTangent;


void main() {
    
    vPosition     = (model * vec4(position, 1.0)).xyz;
    vColor        = color;
    vTexCoord     = texcoord;
    envBoxvNormal = position;
    tNormal       = (model * vec4(normal, 0.0)).xyz;
    tTangent      = cross(tNormal, vec3(0.0, 1.0, 0.0));
    gl_Position   = mvp * vec4(position, 1.0);
}
