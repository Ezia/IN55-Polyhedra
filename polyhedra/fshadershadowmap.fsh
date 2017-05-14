//varying vec4 pos_light; // remove
//varying vec4 color; // remove

//varying vec4 out_position;


//varying vec4 coord;

void main(void)
{
//    gl_FragColor = color;
//    float distToScreen = (pos_light.z + 1.)/2.;
//    distToScreen = gl_FragCoord.z;
//    distToScreen = clamp(gl_FragCoord.w, 0, 1);
//    gl_FragColor = vec4(distToScreen, distToScreen, distToScreen, 1);

    // keep
//    float dist = 1. - (out_position.z/out_position.w + 1.)/2.;




    float dist = gl_FragCoord.z;
    gl_FragColor = vec4(dist, dist, dist, 1);
}
