#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec4 VertexColor;
in vec4 FragPosLightSpace; // from vertex shader

uniform vec3 u_lightColor;
uniform vec3 u_cameraPos;

uniform float u_lightIntensity;
uniform float u_ambientStrength;

uniform sampler2D u_shadowMap;
 

uniform samplerCube u_skybox;
uniform vec3 u_viewPos; // camera position
uniform vec3 u_lightDir;

float u_roughness = 0.4; //0 sharp, 1 soft
;


out vec4 FragColor;


float ShadowCalculation(vec4 fragPosLightSpace)
{
    // Perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;

    // Get closest depth from shadow map
    float closestDepth = texture(u_shadowMap, projCoords.xy).r;

    // Get current depth
    float currentDepth = projCoords.z;

    // Shadow bias to prevent acne
    vec3 norm = normalize(Normal);
    float bias = max(0.01 * (1.0 - dot(norm, -u_lightDir)), 0.005);

    // Check if in shadow
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    // Clamp outside light frustum
    if (projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}


void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(u_viewPos - FragPos);

    // Compute reflection vector
    vec3 reflectDir = reflect(-viewDir, norm);
         reflectDir = normalize(reflectDir + norm * u_roughness); 

    // How strong the reflection is
    float fresnel = pow(1.0 - max(dot(viewDir, norm), 0.0), 3.0);
    float reflectionFactor = mix(0.05, 0.3, fresnel) * (1.0 - u_roughness);

    // Sample skybox in linear space (assuming the cubemap is in linear space)
    vec3 skyboxColor = texture(u_skybox, reflectDir).rgb;

    // Lighting
     vec3 lightDir = normalize(-u_lightDir);
    
    float diff = max(dot(norm,lightDir), 0.0);
    
 float shadow = ShadowCalculation(FragPosLightSpace);

vec3 ambient = u_ambientStrength * u_lightColor * u_lightIntensity;
vec3 diffuse = (1.0 - shadow) * diff * u_lightColor * u_lightIntensity;

vec3 litColor = (ambient + diffuse) * VertexColor.rgb;

vec3 combined = mix(litColor, skyboxColor, reflectionFactor);
combined = pow(combined, vec3(1.0 / 2.2)); // Gamma correction

   FragColor = vec4(combined, VertexColor.a);
}



