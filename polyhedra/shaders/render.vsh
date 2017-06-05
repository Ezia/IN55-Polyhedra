uniform mat4 mvp_matrix;

uniform mat4 spotLightMVP;
uniform vec3 spotLightAmbiant;
uniform vec3 spotLightDiffusion;
uniform vec3 spotLightSpecular;
uniform vec3 spotLightPosition;
uniform mat4 matrixMV;

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
varying vec4 color;
varying vec4 positionInSpotLightProjection;

void main()
{
        gl_Position = mvp_matrix * vec4(a_position, 1);
        color = vec4( a_color, 1.0f );

        normalVec = a_normal;
        normalize(normalVec);
        lightVec = spotLightPosition - a_position;
        normalize(lightVec);
        reflexionVec = 2.*dot(lightVec, normalVec)*normalVec - lightVec;
        normalize(reflexionVec);
        viewVec = (- vec4(matrixMV * vec4(0, 0, 0, 1)) + vec4(matrixMV * vec4(a_position, 1))).xyz;
        normalize(viewVec);

        positionInSpotLightProjection = spotLightMVP * vec4(a_position, 1);
}

