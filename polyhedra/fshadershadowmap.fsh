void main(void)
{
    float dist = gl_FragCoord.z;
    gl_FragColor = vec4(dist, dist, dist, 1);
}
