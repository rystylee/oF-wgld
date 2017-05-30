#version 150
precision mediump float;

uniform vec3 eyePosition;
uniform sampler2DRect normalMap;
uniform samplerCube EnvMap;
uniform int reflection;

in vec3 vPosition;
in vec3 envBoxvNormal;
in vec4 vColor;
in vec2 vTexCoord;
in vec3 tNormal;
in vec3 tTangent;

out vec4 outputColor;

void main(){
    
    vec3 tBinormal = cross(tNormal, tTangent);
    mat3 mView     = mat3(tTangent, tBinormal, tNormal);
    vec3 mNormal   = mView * (texture(normalMap, vTexCoord) * 2.0 - 1.0).rgb;
    
    vec3 ref;
    if(reflection == 1){
        ref = reflect(vPosition - eyePosition, mNormal);
    }else{
        ref = envBoxvNormal;
    }
    
    vec4 envColor  = texture(EnvMap, ref);
    vec4 destColor = vColor * envColor;
    outputColor   = destColor;
}
