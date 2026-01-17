#pragma once
#include "Shader.h"
#include "Mesh.h"
#include "Transform.h"

struct Drawable {
    Mesh* mesh;
    Shader* shader;
    Transform transform;
    float r, g, b, a;
};

class Renderer {
public:
    void draw(const Drawable& obj);
};
