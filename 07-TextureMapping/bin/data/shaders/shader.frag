#version 150
precision mediump float;

// this is how we receive the texture
uniform sampler2DRect tex0;

in vec2 vTextureCoord;
in vec4 vColor;

out vec4 outputColor;

void main(){
    vec4 smpColor = texture(tex0, vTextureCoord);
    outputColor  = vColor * smpColor;
}
