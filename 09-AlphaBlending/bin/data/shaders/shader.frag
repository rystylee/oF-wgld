#version 150
precision mediump float;

// this is how we receive the texture
uniform sampler2DRect tex0;
uniform int useTexture;

in vec2 vTextureCoord;
in vec4 vColor;

out vec4 outputColor;

void main(){
    vec4 destColor = vec4(0.0);
    if(useTexture == 1){
        vec4 smpColor = texture(tex0, vTextureCoord);
        destColor = vColor * smpColor;
    } else {
        destColor = vColor;
    }
    outputColor  = destColor;
}
