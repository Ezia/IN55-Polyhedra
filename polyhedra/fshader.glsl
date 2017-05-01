#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

// lightning
uniform bool a_light; // is the object beeing redered a light ?
varying vec3 diffuse;
varying vec3 vertexLightDir;
varying vec3 vertexCameraDir;
varying vec3 vertexNormalDir;
varying float lightDist2;

void main() {

    if (a_light) {
	gl_FragColor = vec4(gl_Color.rgb,1.0);
    } else {
	float cosTheta = clamp( dot( vertexNormalDir, vertexLightDir), 0,1 );

	gl_FragColor =
	// Ambient : simulates indirect lighting
	gl_LightSource[0].ambient*gl_Color +
	// Diffuse : "color" of the object
	gl_LightSource[0].diffuse*gl_Color * cosTheta / lightDist2 ;

	//    gl_FragColor = vec4( gl_Color.rgb, 1.0f );
//	    gl_FragColor =  gl_LightSource[0].ambient + (diffuse *
//	vec4(gl_Color.rgb,1.0));// + (specular * gl_Color.a);
    }

}

//! [0]

