#version 150
precision mediump float;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 mvp;
uniform mat4 inv;
uniform vec3 lightPosition;
uniform vec3 eyeDirection;
uniform vec4 ambientColor;

in vec3 position;
in vec3 normal;
in vec4 color;
in vec2 texcoord;

out vec4 vColor;
out vec2 vTexCoord;
out vec3 vEyeDirection;
out vec3 vLightDirection;

void main() {
    
    vec3 pos      = (model * vec4(position, 0.0)).xyz;
    vec3 invEye   = (inv * vec4(eyeDirection, 0.0)).xyz;
    vec3 invLight = (inv * vec4(lightPosition, 0.0)).xyz;
    vec3 eye      = invEye - pos;
    vec3 light    = invLight - pos;
    vec3 n = normalize(normal);
    vec3 t = normalize(cross(normal, vec3(0.0, 1.0, 0.0)));
    vec3 b = cross(n, t);
    vEyeDirection.x   = dot(t, eye);
    vEyeDirection.y   = dot(b, eye);
    vEyeDirection.z   = dot(n, eye);
    normalize(vEyeDirection);
    vLightDirection.x = dot(t, light);
    vLightDirection.y = dot(b, light);
    vLightDirection.z = dot(n, light);
    normalize(vLightDirection);
    vColor     = color;
    vTexCoord  = texcoord;
    gl_Position    = mvp * vec4(position, 1.0);
    
}
