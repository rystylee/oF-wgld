#version 150
precision mediump float;

uniform mat4 inv;
uniform vec3 lightDirection;
uniform sampler2DRect tex0;
uniform vec4 edgeColor;

in vec3 vPosition;
in vec3 vNormal;
in vec4 vColor;

out vec4 outputColor;

void main(){
    if(edgeColor.a > 0.0){
        outputColor = edgeColor;
    }else{
        vec3 invLight = normalize(inv * vec4(lightDirection, 0.0)).xyz;
        float diffuse = clamp(dot(vNormal, invLight), 0.0, 1.0);
        //vec4 smpColor = texture(tex0, vec2(diffuse, 0.0));
        
        if(diffuse < 0.1){
            diffuse = 0.1;
        } else if(diffuse >= 0.1 && diffuse < 0.5){
            diffuse = 0.5;
        } else {
            diffuse = 1.0;
        }
        
        //outputColor = vColor * smpColor;
        outputColor = vColor * vec4(vec3(diffuse), 1.0);
    }
}
