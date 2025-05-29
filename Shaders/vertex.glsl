#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;   // World-space position
out vec3 Normal;    // World-space normal

void main()
{
    // Transform vertex position to world space
    vec4 worldPosition = model * vec4(aPos, 1.0);
    FragPos = vec3(worldPosition);

    // Transform normal to world space (handles scaling and rotation)
    Normal = mat3(transpose(inverse(model))) * aNormal;

    // Final clip-space position
    gl_Position = projection * view * worldPosition;
}