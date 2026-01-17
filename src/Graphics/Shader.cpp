#include "Shader.h"


Shader::Shader(const char* vertexShader, const char* fragmentShader) {
    unsigned int v = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v, 1, &vertexShader, nullptr);
    glCompileShader(v);

    unsigned int f = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f, 1, &fragmentShader, nullptr);
    glCompileShader(f);

    id = glCreateProgram();
    glAttachShader(id, v);
    glAttachShader(id, f);
    glLinkProgram(id);

    glDeleteShader(v);
    glDeleteShader(f);
}

void Shader::use() const {
    glUseProgram(id);
}

void Shader::setVec2(const char* name, float x, float y) const {
    glUniform2f(glGetUniformLocation(id, name), x, y);
}

void Shader::setVec3(const char* name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(id, name), x, y, z);
}

void Shader::setVec4(const char* name, float r, float g, float b, float a) const {
    glUniform4f(glGetUniformLocation(id, name), r, g, b, a);
}
