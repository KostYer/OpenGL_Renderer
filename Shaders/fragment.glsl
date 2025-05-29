#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec4 VertexColor;

uniform vec3 u_lightPos;
uniform vec3 u_lightDir;
uniform vec3 u_lightColor;

void main() {
    vec3 norm = normalize(Normal);
     vec3 lightDir = normalize(u_lightPos - FragPos);
    
     float diff = max(dot(norm, normalize(u_lightDir)), 0.0);
    
     float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * u_lightColor;
   vec3 diffuse = diff * u_lightColor;

    vec3 result = (ambient + diffuse) * VertexColor.rgb;
   FragColor = vec4(result, VertexColor.a);
   // FragColor = VertexColor;
    
}