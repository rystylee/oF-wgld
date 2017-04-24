#version 150
precision mediump float;

// this is how we receive the texture
uniform sampler2DRect tex0;
uniform sampler2DRect tex1;

in vec2 vTextureCoord;
in vec4 vColor;

out vec4 outputColor;

void main(){
    vec4 smpColor0 = texture(tex0, vTextureCoord);
    vec4 smpColor1 = texture(tex1, vTextureCoord);
    outputColor  = vColor * smpColor0 * smpColor1;
}
