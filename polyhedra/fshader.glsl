#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform vec3 spotLightAmbiant;
uniform vec3 spotLightDiffusion;
uniform vec3 spotLightSpecular;

varying vec4 positionInSpotLightProjection;

uniform sampler2D spotLightDepth;

varying vec3 normalVec;
varying vec3 lightVec;
varying vec3 reflexionVec;
varying vec3 viewVec;


void main() {

        float inSpotLight = 1.;

        vec3 spotPos = (positionInSpotLightProjection.xyz/positionInSpotLightProjection.w +1.)/2.;
        if ((spotPos.x) > 1. || spotPos.x < 0.) {
            inSpotLight = 0.;
        } else if ((spotPos.y) > 1. || spotPos.y < 0.) {
            inSpotLight = 0.;
        } else if ((spotPos.z) > 1. || spotPos.z < 0.) {
            inSpotLight = 0.;
        } else if ((texture2D(spotLightDepth, spotPos.xy).z)+0.005 < (spotPos.z)) {
            inSpotLight = 0.;
        }

        gl_FragColor = gl_Color*(vec4(spotLightAmbiant ,1)
                + inSpotLight*(
                    clamp(dot(lightVec, normalVec), 0, 1)*vec4(spotLightDiffusion, 1)
//                    + pow(clamp(dot(reflexionVec, viewVec), 0, 1), 1)*vec4(spotLightSpecular, 1)
                ));
}


