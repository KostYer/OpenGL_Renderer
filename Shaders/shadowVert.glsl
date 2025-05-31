// shadow_depth.vert
#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 lightSpaceMatrix; // light's projection * view
uniform mat4 model;

void main()
{
    gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);
}