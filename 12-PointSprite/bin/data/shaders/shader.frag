#version 150
precision mediump float;

uniform sampler2D tex0;
uniform int useTexture;

in vec2 vTextureCoord;
in vec4 vColor;

out vec4 outputColor;

void main(){
    vec4 smpColor = vec4(1.0);
    if(useTexture == 1){
        smpColor = texture(tex0, gl_PointCoord);
    }
    if(smpColor.a == 0.0){
        discard;
    }else{
        outputColor = vColor * smpColor;
    }
}
