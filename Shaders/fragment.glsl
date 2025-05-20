#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;


uniform vec3 u_lightPos;
uniform vec3 u_lightDir;
uniform vec3 u_lightColor;

vec4 objectColor = vec4(0.8, 0.3, 0.2, 1.0);


void main() {

     // FragColor = vec4(0.8, 0.3, 0.2, 1.0); // Just red-ish
       // Normalize input normal
      vec3 norm = normalize(Normal);
    
     // Direction from fragment to light source
     vec3 lightDir = normalize(u_lightPos - FragPos);
    
    // Diffuse shading
    float diff = max(dot(norm, u_lightDir), 0.0);
    
    // Ambient component
     float ambientStrength = 0.1;
     vec3 ambient = ambientStrength *  u_lightColor;
    
    // Diffuse component
     vec3 diffuse = diff * u_lightColor;
    
    // Final color calculation
    vec3 result = (ambient + diffuse) * objectColor.rgb;
     FragColor = vec4(result, 1.0);
//



}