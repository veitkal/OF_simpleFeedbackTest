#version 150

/*Heavily inspired by Andrei Jay,
  https://github.com/ex-zee-ex/intro_to_digital_feedback
  modified and converted to openGL 3 by Jakob Jennerholm Hammar

  hsv2rgb/rgb2hsv algorithm written by http://lolengine.net/blog/2013/07/27/rgb-to-hsv-in-glsl

  Contrast by Patricio Gonzalez Vivo patriciogonzalezvivo

*/

//tex0 will always be the first texture that you bind to the gpu
uniform sampler2DRect tex0;

uniform vec2 uFeedDisp;
uniform float uFeedMix;
uniform float uFeedAlpha;
uniform vec4 uFeedHsv;
uniform float uFeedBrightness;
uniform float uFeedContrast;
uniform int uFeedMixToggle;

//texCoordVarying is declared over in the vertex shader, this is the x y coordinate of which pixel the gpu is drawing on the screen.  this varies per frame so thats why this datatype is called varying. generally speaking variables defined within the shaders are varying because they change with each pixel and variables definied within oF (or whatever wrapper yr using to send info to shaders) will be uniform because they are the same for each pixel but can change on a frame by frame basis
in vec2 v_texCoord;

//vec3 rgb2hsv(vec3 c);
//vec3 hsv2rgb(vec3 c);

out vec4 outputColor;



void brightnessAdjust( inout vec4 color, in float b) {
    color.rgb += b;
}

void contrastAdjust( inout vec4 color, in float c) {
    float t = 0.5 - c * 0.5;
    color.rgb = color.rgb * c + t;
}



void main()
{
     vec4 color = vec4(0.0,0.0,0.0,0.0);

    //lets grab the color from the feedback texture
    //texture2DRect is a function that takes two arguments, a texture and a vec2 and then returns the pixel information from the texture at the (x,y) location given by the vec2 components in the form (red, green, blue, alpha) where each value is normalized between 0 and 1.

    //we want to grab the color from the current location first
    vec4 tex0_color=texture2DRect(tex0, v_texCoord);


    //and then grab a color from a displaced location so that we can perform an implicit convolution
    vec4 feedback_color=texture2DRect(tex0, v_texCoord+uFeedDisp);

    //and we will need to also change some aspects of the values of the pixels to get color based feedback as well!
    //feedback_color.g=1.1*tex0_color.g;
    //feedback_color.g=fract(tex0_color.g);
    //feedback_color.g=1.1*tex0_color.g;

    //feedback_color=mix(uFeedHsv, tex0_color);

    vec4 tempColor = vec4(0.0,0.0,0.0,0.0);
    tempColor.r = mix(feedback_color.r, fract(tex0_color.r), uFeedHsv.r);
    tempColor.g = mix(feedback_color.g, fract(tex0_color.g), uFeedHsv.g);
    tempColor.b = mix(feedback_color.b, fract(tex0_color.b), uFeedHsv.b);
    tempColor.a = mix(feedback_color.a, fract(tex0_color.a), uFeedHsv.a);
    feedback_color = tempColor;

    contrastAdjust(feedback_color, uFeedContrast);
    brightnessAdjust(feedback_color, uFeedBrightness);

    if (uFeedMixToggle==0) {
    //mix color with displaced channel
    color=uFeedMix*feedback_color;
    } else {
    ///or try mixxxitwithitself!
    color=mix(tex0_color,feedback_color,uFeedMix);
}


   /* CONVERT rgb2hsv hsv2rgb .
    Not used now but saving to use with hsv later*/
    //vec3 tempColorHsv = rgb2hsv(color.rgb);
    //tempColorHsv.r = 0;
    //vec3 tempColorRgb = hsv2rgb(tempColorHsv);
    //color.rgb = tempColorRgb;

    //brightness

//    float p = 0.3 *color.g + 0.59*color.r + 0.11*color.b;
//    p = p * uFeedBrightness;
//    color = vec4(p,p,p,1.0);
//    color = mix( vec4(1.0,1.0,1.0,1.0),color,uFeedContrast);

//    contrastAdjust(color, uFeedContrast);
//    brightnessAdjust(color, uFeedBrightness);
    //alphaControl
    color.a = uFeedAlpha;

    //gl_FragColor = color;
    outputColor = color;

}
vec3 rgb2hsv(vec3 c) {

    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}
