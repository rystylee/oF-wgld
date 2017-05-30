#version 150
precision mediump float;

uniform vec3 eyePosition;
uniform samplerCube	EnvMap;
uniform float eta;
uniform int reflection;

in vec3 vPosition;
in vec3 vNormal;
in vec3 envBoxvNormal;
in vec4 vColor;
in vec2 vTexCoord;

out vec4 outputColor;

void main(){
    
    vec3 ref;
    if(reflection == 1){
        ref = refract(normalize(vPosition - eyePosition), vNormal, eta);
    }else{
        //ref = vNormal;
        ref = envBoxvNormal;
    }
    
    vec4 envColor  = texture(EnvMap, ref);
    vec4 destColor = vColor * envColor;
    outputColor   = destColor;
}
