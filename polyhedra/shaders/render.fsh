struct Light
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
    mat4 mvp;
};

struct DepthMap
{
    sampler2D map;
    float bias;
};

// light
uniform Light light;

// depth map from the light point of view
uniform DepthMap depthMap;

// vertex data for illumination
varying vec4 FPositionInLight;
varying vec3 FNormal;
varying vec3 FLightVec;
varying vec3 FReflexionVec;
varying vec3 FViewVec;
varying vec3 FColor;

void main()
{
    // normalize vectors
    vec3 FNormalNorm = normalize(FNormal);
    vec3 FLightVecNorm = normalize(FLightVec);
    vec3 FReflexionVecNorm = normalize(FReflexionVec);
    vec3 FViewVecNorm = normalize(FViewVec);

    // determine if the fragment is in the spotlight
    bool inSpotLight = true;
    vec3 spotPos = (FPositionInLight.xyz/FPositionInLight.w +1.)/2.;
    if ((spotPos.x) > 1. || spotPos.x < 0.) {
        inSpotLight = false;
    } else if ((spotPos.y) > 1. || spotPos.y < 0.) {
        inSpotLight = false;
    } else if ((spotPos.z) > 1. || spotPos.z < 0.) {
        inSpotLight = false;
    } else if ((texture2D(depthMap.map, spotPos.xy).z)+depthMap.bias < (spotPos.z)) {
        inSpotLight = false;
    }

    // ambient light
    vec3 ambient = FColor*(light.ambient);

    if (inSpotLight == true)
    {
        // diffuse light
        vec3 diffuse = FColor*(light.diffuse)
                *max(0., dot(FLightVecNorm, FNormalNorm));

        // specular light
        vec3 specular = light.specular
                *pow(max(0., dot(FViewVecNorm, FReflexionVecNorm)), 10.);

        gl_FragColor = vec4(ambient + diffuse + specular, 1.);
    }
    else
    {
        gl_FragColor = vec4(ambient, 1.);
    }
}


