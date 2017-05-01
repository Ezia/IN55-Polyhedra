#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

// Transform matrices
uniform mat4 mvp_matrix;
uniform mat4 mv_matrix;

// lightning
uniform bool a_light; // is the object beeing redered a light ?
varying vec3 diffuse;
varying vec3 vertexLightDir;
varying vec3 vertexCameraDir;
varying vec3 vertexNormalDir;
varying float lightDist2;

// vertex data
attribute vec3 a_position;
attribute vec3 a_color;
attribute vec3 a_normal;

void main()
{
    if (a_light) {
	gl_FrontColor = vec4( 1, 1, 1, 1.0f );
	gl_Position = mvp_matrix * vec4(a_position, 1);
    } else {
	// Calculate vertex position in screen space
	gl_Position = mvp_matrix * vec4(a_position, 1);

	gl_FrontColor = vec4( a_color, 1.0f );


	// Vector that goes from the vertex to the camera, in camera space.
	// In camera space, the camera is at the origin (0,0,0).
	vec4 position_mv = (mv_matrix * vec4(a_position, 1));
	vec3 eyeDir_mv = vec3(0,0,0) - position_mv.xyz;
	vertexCameraDir = normalize(eyeDir_mv);

	// Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
	vec4 lightPosition_mv = ( mv_matrix * gl_LightSource[0].position);
	vec3 lightDir_mv = lightPosition_mv.xyz - position_mv.xyz;
	lightDist2 = length(lightDir_mv);
	vertexLightDir = normalize(lightDir_mv);

	vertexNormalDir = vec4(mv_matrix * vec4(a_normal,0)).xyz;

	// Normal of the the vertex, in camera space
	// Only correct if ModelMatrix does not scale the model !
//	vec3 normal_mv = ( mv_matrix * vec4(a_normal,0));
    }


//    float
//     specularPower = 0.0;
//    if
//    (nxDir != 0.0)
//      {
//	vec3 cameraVector = normalize(CAMERA_POSITION - gl_Vertex.xyz);
//	vec3 halfVector = normalize(lightVector + cameraVector);
//	float nxHalf = max(0.0,dot(normal, halfVector));
//	specularPower = pow(nxHalf, 0.2);
//    }
//    specular = gl_LightSource[0].specular* specularPower;
    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
//    v_texcoord = a_texcoord;


    //vec3 normal = gl_NormalMatrix * gl_Normal; // Usually your lights won't be in world space,
    //so you have to multiply the normal by the normal matrix to have it in world space.
    //	vec3 normal = a_normal; // Normals are expected to be normalized. If they are not, do it here.
    //	vec3 lightVector = normalize(gl_LightSource[0].position.xyz);
    //	float nxDir = max(0.0, dot(normal, lightVector));
    //	// Normal x light direction.
    //	diffuse = gl_LightSource[0].diffuse * nxDir;
}

