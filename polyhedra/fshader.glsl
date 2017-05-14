#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform vec3 spotLightAmbiant;
uniform vec3 spotLightDiffusion;
uniform float width;
uniform float height;

// lightning
//varying float lightDist;
varying vec4 positionInSpotLightProjection;
//varying float lightning; // 0 if the face is back to the light)

//uniform bool a_light; // is the object beeing redered a light ?
//varying vec3 diffuse;
//varying vec3 vertexLightDir;
//varying vec3 vertexCameraDir;
//varying vec3 vertexNormalDir;
//varying float lightDist2;
//varying vec4 pixel;
//varying vec4 lightProj;
//varying vec4 positionInSpotLightProjection;

uniform sampler2D spotLightDepth;
varying vec4 coord;
void main() {

//    if (a_light) {
//	gl_FragColor = vec4(gl_Color.rgb,1.0);
//    } else {
        float inSpotLight = 1.;
//        float wLightSpot = positionInSpotLightProjection.w;

        vec3 spotPos = (positionInSpotLightProjection.xyz/positionInSpotLightProjection.w +1.)/2.;
        if (/*abs*/(spotPos.x) > 1. || spotPos.x < 0.) {
            inSpotLight = 0.;
        } else if (/*abs*/(spotPos.y) > 1. || spotPos.y < 0.) {
            inSpotLight = 0.;
        } else if (/*abs*/(spotPos.z) > 1. || spotPos.z < 0.) {
            inSpotLight = 0.;
        } else if ((texture2D(spotLightDepth, spotPos.xy).z)+0.005 < (spotPos.z)) {
            inSpotLight = 0.;
        }

//        float cosTheta = clamp( dot( vertexNormalDir, vertexLightDir), 0.0f, 1.0f );

        gl_FragColor = vec4(spotLightAmbiant ,1)*gl_Color + inSpotLight*vec4(spotLightDiffusion, 1)*gl_Color/*/ lightDist*/ ;

//        gl_FragColor = /*inSpotLight**/texture2D(spotLightDepth, spotPos.xy);


//        gl_FragColor = texture2D(spotLightDepth, spotPos.xy);
//        float distToCam = (coord.z/coord.w +1.)/2.;
//        gl_FragColor = vec4(distToCam, distToCam, distToCam, 1);

//        gl_FragColor = texture2D(spotLightDepth, (coord.xy/coord.w + 1.)/2.);

//        if (gl_FragCoord.x > 1.) {
//            gl_FragColor = vec4(1, 0, 0, 1);
//        }

//        vec4 fragToLight = lightProj - gl_FragCoord;
//        float dist = sqrt(dot(fragToLight.xyz, fragToLight.xyz));
//        dist = (1.+gl_FragCoord.z)/2.;
//        gl_FragColor = vec4(dist, dist, dist, 1);
//        gl_FragColor = vec4((gl_FragCoord.z)/2, 1.-gl_FragCoord.z/2, 1.-gl_FragCoord.z/2, 1);

	//    gl_FragColor = vec4( gl_Color.rgb, 1.0f );
//	    gl_FragColor =  gl_LightSource[0].ambient + (diffuse *
//	vec4(gl_Color.rgb,1.0));// + (specular * gl_Color.a);


//    }
}

//! [0]

