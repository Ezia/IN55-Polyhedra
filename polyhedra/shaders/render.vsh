uniform mat4 mvp_matrix;

uniform mat4 spotLightMVP;
uniform vec3 spotLightAmbiant;
uniform vec3 spotLightDiffusion;
uniform vec3 spotLightSpecular;
uniform vec3 spotLightPosition;
uniform mat4 matrixMV;
uniform mat4 invMatrixMV;

uniform float shadowBias;
uniform sampler2D spotLightDepth;

// vertex data
attribute vec3 a_position;
attribute vec3 a_color;
attribute vec3 a_normal;

varying vec3 normalVec;
varying vec3 lightVec;
varying vec3 reflexionVec;
varying vec3 viewVec;
varying vec3 color;
varying vec4 positionInSpotLightProjection;

void main()
{
        gl_Position = mvp_matrix * vec4(a_position, 1);
        color = a_color;

        normalVec = a_normal;
        lightVec = spotLightPosition - a_position;
        reflexionVec = reflect(lightVec, normalVec);
        viewVec = vec3(invMatrixMV * vec4(0.0, 0.0, 0.0, 1.0) - vec4(a_position, 1));

        positionInSpotLightProjection = spotLightMVP * vec4(a_position, 1);
}

