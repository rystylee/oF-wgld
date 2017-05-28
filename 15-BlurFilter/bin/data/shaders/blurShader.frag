#version 150
precision mediump float;

// this is how we receive the texture
uniform sampler2DRect fbo;
uniform int useBlur;

in vec2 vTexCoord;
in vec4 vColor;
in vec4 vPosition;

out vec4 outputColor;

void main(){
    float xFrag = 1.0 / 1024.0;
    float yFrag = 1.0 / 768.0;

    vec4 destColor = texture(fbo, gl_FragCoord.xy);
    
    if(useBlur == 0){
        destColor *= 0.36;
        destColor += texture(fbo, vec2(gl_FragCoord.s + (-2.0), gl_FragCoord.t + ( 2.0))) * 0.04;
        destColor += texture(fbo, vec2(gl_FragCoord.s + ( 0.0), gl_FragCoord.t + ( 2.0))) * 0.04;
        destColor += texture(fbo, vec2(gl_FragCoord.s + ( 2.0), gl_FragCoord.t + ( 2.0))) * 0.04;
        destColor += texture(fbo, vec2(gl_FragCoord.s + (-2.0), gl_FragCoord.t + ( 0.0))) * 0.04;
        destColor += texture(fbo, vec2(gl_FragCoord.s + ( 2.0), gl_FragCoord.t + ( 0.0))) * 0.04;
        destColor += texture(fbo, vec2(gl_FragCoord.s + (-2.0), gl_FragCoord.t + (-2.0))) * 0.04;
        destColor += texture(fbo, vec2(gl_FragCoord.s + ( 0.0), gl_FragCoord.t + (-2.0))) * 0.04;
        destColor += texture(fbo, vec2(gl_FragCoord.s + ( 2.0), gl_FragCoord.t + (-2.0))) * 0.04;
        destColor += texture(fbo, vec2(gl_FragCoord.s + (-4.0), gl_FragCoord.t + ( 4.0))) * 0.02;
        destColor += texture(fbo, vec2(gl_FragCoord.s + (-2.0), gl_FragCoord.t + ( 4.0))) * 0.02;
        destColor += texture(fbo, vec2(gl_FragCoord.s + ( 0.0), gl_FragCoord.t + ( 4.0))) * 0.02;
        destColor += texture(fbo, vec2(gl_FragCoord.s + ( 2.0), gl_FragCoord.t + ( 4.0))) * 0.02;
        destColor += texture(fbo, vec2(gl_FragCoord.s + ( 4.0), gl_FragCoord.t + ( 4.0))) * 0.02;
        destColor += texture(fbo, vec2(gl_FragCoord.s + (-4.0), gl_FragCoord.t + ( 2.0))) * 0.02;
        destColor += texture(fbo, vec2(gl_FragCoord.s + ( 4.0), gl_FragCoord.t + ( 2.0))) * 0.02;
        destColor += texture(fbo, vec2(gl_FragCoord.s + (-4.0), gl_FragCoord.t + ( 0.0))) * 0.02;
        destColor += texture(fbo, vec2(gl_FragCoord.s + ( 4.0), gl_FragCoord.t + ( 0.0))) * 0.02;
        destColor += texture(fbo, vec2(gl_FragCoord.s + (-4.0), gl_FragCoord.t + (-2.0))) * 0.02;
        destColor += texture(fbo, vec2(gl_FragCoord.s + ( 4.0), gl_FragCoord.t + (-2.0))) * 0.02;
        destColor += texture(fbo, vec2(gl_FragCoord.s + (-4.0), gl_FragCoord.t + (-4.0))) * 0.02;
        destColor += texture(fbo, vec2(gl_FragCoord.s + (-2.0), gl_FragCoord.t + (-4.0))) * 0.02;
        destColor += texture(fbo, vec2(gl_FragCoord.s + ( 0.0), gl_FragCoord.t + (-4.0))) * 0.02;
        destColor += texture(fbo, vec2(gl_FragCoord.s + ( 2.0), gl_FragCoord.t + (-4.0))) * 0.02;
        destColor += texture(fbo, vec2(gl_FragCoord.s + ( 4.0), gl_FragCoord.t + (-4.0))) * 0.02;
    }

    outputColor  = destColor;
    
}
