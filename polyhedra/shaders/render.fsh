uniform vec3 spotLightAmbiant;
uniform vec3 spotLightDiffusion;
uniform vec3 spotLightSpecular;
uniform float shadowBias;

varying vec4 positionInSpotLightProjection;

uniform sampler2D spotLightDepth;

varying vec3 normalVec;
varying vec3 lightVec;
varying vec3 reflexionVec;
varying vec3 viewVec;
varying vec4 color;

void main() {
        normalize(normalVec);
        normalize(lightVec);
        normalize(reflexionVec);
        normalize(viewVec);


        float inSpotLight = 1.;

        vec3 spotPos = (positionInSpotLightProjection.xyz/positionInSpotLightProjection.w +1.)/2.;
        if ((spotPos.x) > 1. || spotPos.x < 0.) {
            inSpotLight = 0.;
        } else if ((spotPos.y) > 1. || spotPos.y < 0.) {
            inSpotLight = 0.;
        } else if ((spotPos.z) > 1. || spotPos.z < 0.) {
            inSpotLight = 0.;
        } else if ((texture2D(spotLightDepth, spotPos.xy).z)+shadowBias < (spotPos.z)) {
            inSpotLight = 0.;
        }

        gl_FragColor = //clamp(
                        color*vec4(spotLightAmbiant ,1)
                        + inSpotLight*color*dot(lightVec, normalVec)*vec4(spotLightDiffusion, 1)
                        + inSpotLight*vec4(pow(clamp(dot(viewVec, reflexionVec), 0., 1.), 1000)*spotLightSpecular, 1.)
//                    ,0., 1.)
                ;
}


