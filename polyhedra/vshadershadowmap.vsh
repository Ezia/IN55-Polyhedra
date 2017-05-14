//uniform mat4 MVP; // remove
//uniform mat4 lightMVP; // remove
uniform mat4 spotLightMVP;

attribute vec3 in_position;
//attribute vec3 a_position; // remove
//attribute vec3 a_color; // remove

//varying vec4 pos_light; // remove
//varying vec4 color; // remove

//varying vec4 out_position;

//varying vec4 coord;

void main(void)
{
//    mat4 proj = spotLightMVP;
//    gl_Position = MVP * vec4(a_position, 1);
//    gl_Position = proj * vec4(in_position, 1);
//    pos_light = proj * vec4(in_position, 1);
//    color = vec4(a_color, 1);

    // keep
//    out_position = spotLightMVP * vec4(in_position, 1);
    gl_Position = spotLightMVP * vec4(in_position, 1);
//    coord = spotLightMVP * vec4(in_position, 1);
}


