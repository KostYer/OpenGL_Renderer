#pragma once
#include <string>
#include <glad/gl.h>

class Shader {
public:
    GLuint ID;
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    void use() const;
    void setMat4(const std::string& name, const float* value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setFloat(const std::string& name, float value) const;
};