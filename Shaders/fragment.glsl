#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec4 VertexColor;

uniform vec3 u_lightPos;
uniform vec3 u_lightColor;
uniform vec3 u_cameraPos;

uniform float u_lightIntensity;
uniform float u_ambientStrength;

uniform samplerCube u_skybox;
uniform vec3 u_viewPos; // camera position
float u_roughness = 0.4; //0 sharp, 1 soft
 

out vec4 FragColor;

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
    vec3 lightDir = normalize(u_lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    
    vec3 ambient = u_ambientStrength * u_lightColor * u_lightIntensity;
    vec3 diffuse = diff * u_lightColor * u_lightIntensity;

    vec3 litColor = (ambient + diffuse) * VertexColor.rgb;

    // Combine lit color and skybox in linear space
    vec3 combined = mix(litColor, skyboxColor, reflectionFactor); // Blend factor to taste

    // Final gamma correction — only once!
    combined = pow(combined, vec3(1.0 / 2.2));

    FragColor = vec4(combined, VertexColor.a);
}
