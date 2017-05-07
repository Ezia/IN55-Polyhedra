varying vec4 pos_light;
varying vec4 color;
void main(void)
{
    gl_FragColor = color;
    float distToScreen = (pos_light.z + 1.)/2.;
    distToScreen = gl_FragCoord.z;
//    distToScreen = clamp(gl_FragCoord.w, 0, 1);
    gl_FragColor = vec4(distToScreen, distToScreen, distToScreen, 1);
}
