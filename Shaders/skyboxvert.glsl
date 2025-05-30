#version 330 core
layout(location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 view;
uniform mat4 projection;

void main() {
    // Remove translation from the view matrix
    mat4 rotView = mat4(mat3(view));
    vec4 pos = projection * rotView * vec4(aPos, 1.0);
    gl_Position = pos.xyww;  //forces the Z depth to always be 1.0
    TexCoords = aPos;

   //gl_Position = projection * view * vec4(position, 1.0);
}