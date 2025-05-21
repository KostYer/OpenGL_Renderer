#version 330 core
in vec3 TexCoords;
out vec4 FragColor;

 uniform samplerCube u_skybox;

void main() {
     FragColor = texture(u_skybox, TexCoords);
  // FragColor = vec3(0.0, 0.0, 1.0);

}