#version 150
precision mediump float;

// this is how we receive the texture
uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
uniform int texManage;

in vec2 vTextureCoord;
in vec4 vColor;

out vec4 outputColor;

void main(){
    vec4 smpColor;
    if(texManage == 0){
        smpColor = texture(tex0, vTextureCoord);
    } else {
        smpColor = texture(tex1, vTextureCoord);
    }
    outputColor  = vColor * smpColor;
}
