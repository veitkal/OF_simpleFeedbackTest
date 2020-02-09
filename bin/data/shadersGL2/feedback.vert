#version 150

uniform mat4 modelViewProjectionMatrix;
in vec4 position;
in vec2 texcoord;

out vec2 v_texCoord;

void main(){
    v_texCoord = texcoord;
    gl_Position = modelViewProjectionMatrix * position;
}

//#version 120

//varying vec2 texCoordVarying;

//void main(void)
//{
//        texCoordVarying = gl_MultiTexCoord0.xy;
//        gl_Position = ftransform();
//}
