struct Light
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
    mat4 mvp;
};

// light data
uniform Light light;

// mvp matrices
uniform mat4 mvp;
uniform mat4 invMv;

// vertex data
attribute vec3 VPosition;
attribute vec3 VColor;
attribute vec3 VNormal;

// vertex data for illumination
varying vec3 FNormal;
varying vec3 FLightVec;
varying vec3 FReflexionVec;
varying vec3 FViewVec;
varying vec3 FColor;
varying vec4 FPositionInLight;

void main()
{
    // position
    gl_Position = mvp * vec4(VPosition, 1);

    // color
    FColor = VColor;

    // illumination data
    FNormal = VNormal;
    FLightVec = light.position - VPosition;
    FReflexionVec = reflect(-FLightVec, FNormal);
    FViewVec = vec3(invMv * vec4(0.0, 0.0, 0.0, 1.0) - vec4(VPosition, 1));
    FPositionInLight = light.mvp * vec4(VPosition, 1);
}

