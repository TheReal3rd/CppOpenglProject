#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Mesh {
public:
    unsigned int VAO;
    unsigned int indexCount;

    Mesh(const float* vertices, size_t vSize, const unsigned int* indices, size_t iSize);
    void draw() const;
};


