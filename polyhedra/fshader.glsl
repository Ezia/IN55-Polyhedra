#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

//uniform sampler2D texture;

//varying vec2 v_texcoord;

////! [0]
//void main()
//{
//    // Set fragment color from texture
//    // gl_FragColor = texture2D(texture, v_texcoord);
//    gl_FragColor = vec4( gl_Color.rgb, 1.0f );
//    gl_LightSource[0].ambient.rgb;
//}


varying vec4 diffuse;
//varying vec4 specular;

void main() {
//    gl_FragColor = vec4( gl_Color.rgb, 1.0f );
    gl_FragColor =  gl_LightSource[0].ambient + (diffuse *
vec4(gl_Color.rgb,1.0));// + (specular * gl_Color.a);
}

//! [0]

