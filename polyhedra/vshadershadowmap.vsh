uniform mat4 spotLightMVP;

attribute vec3 in_position;


void main(void)
{
    gl_Position = spotLightMVP * vec4(in_position, 1);
}


