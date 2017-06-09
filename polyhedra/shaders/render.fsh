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
varying vec3 color;


void main() {
        vec3 f_normalVec = normalize(normalVec);
        vec3 f_lightVec = normalize(lightVec);
        vec3 f_reflexionVec = normalize(reflexionVec);
        vec3 f_viewVec = normalize(viewVec);

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

        vec3 ambiant = color*spotLightAmbiant;

        vec3 diffuse = color*spotLightDiffusion
                *max(0., dot(f_lightVec, f_normalVec));

        vec3 specular;
        if (dot(f_normalVec, f_lightVec) < 0.0) { // light source on the wrong side?
            specular = vec3(0.0, 0.0, 0.0); // no specular reflection
        } else {
            specular = /*color**/spotLightSpecular
                *pow(max(0., dot(f_viewVec, f_reflexionVec)), 10.);
        }

        gl_FragColor = vec4(ambiant+ inSpotLight*(diffuse + specular), 1.);

}


