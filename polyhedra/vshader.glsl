#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;

attribute vec4 a_position;
//attribute vec2 a_texcoord;
attribute vec3 a_color;
attribute vec3 a_normal;

varying vec4 diffuse;
//varying vec4 specular;
//uniform vec3 CAMERA_POSITION;
//varying vec2 v_texcoord;

//! [0]
void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * a_position;

    gl_FrontColor = vec4( a_color, 1.0f );

    //vec3 normal = gl_NormalMatrix * gl_Normal; // Usually your lights won't be in world space,
    //so you have to multiply the normal by the normal matrix to have it in world space.
    vec3 normal = a_normal; // Normals are expected to be normalized. If they are not, do it here.
    vec3 lightVector = normalize(gl_LightSource[0].position.xyz);
    float nxDir = max(0.0, dot(normal, lightVector));
    // Normal x light direction.
    diffuse = gl_LightSource[0].diffuse * nxDir;

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
}
//! [0]
