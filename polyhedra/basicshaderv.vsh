
uniform mat4 MVP;

attribute vec3 position;
attribute vec3 in_color;
varying vec4 out_color;

void main(void)
{
    gl_Position = MVP * vec4(position, 1);
    out_color = vec4(in_color, 1);
}


