#pragma once
#include <glad/glad.h>

class Shader {
public:
    unsigned int id;

    Shader(const char* vertexShader, const char* fragmentShader);
    void use() const;

    void setVec2(const char* name, float x, float y) const;
    void setVec3(const char* name, float x, float y, float z) const;
    void setVec4(const char* name, float r, float g, float b, float a) const;
};