#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;

uniform mat4 spotLightMVP;
uniform vec3 spotLightAmbiant;
uniform vec3 spotLightDiffusion;

uniform sampler2D spotLightDepth;

// vertex data
attribute vec3 a_position;
attribute vec3 a_color;
attribute vec3 a_normal;

varying vec4 positionInSpotLightProjection;

void main()
{

        gl_Position = mvp_matrix * vec4(a_position, 1);

	gl_FrontColor = vec4( a_color, 1.0f );

        vec4 tmp = spotLightMVP * vec4(a_position, 1);

        positionInSpotLightProjection = tmp;

}

