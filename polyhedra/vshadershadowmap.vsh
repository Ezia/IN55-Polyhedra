uniform mat4 MVP;
uniform mat4 lightMVP;

attribute vec3 a_position;
attribute vec3 a_color;

varying vec4 pos_light;
varying vec4 color;

void main(void)
{
//    gl_Position = MVP * vec4(a_position, 1);
    gl_Position = lightMVP * vec4(a_position, 1);
    pos_light = lightMVP * vec4(a_position, 1);
    color = vec4(a_color, 1);
}


