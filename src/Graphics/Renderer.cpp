#include "Renderer.h"
    

void Renderer::draw(const Drawable& obj) {
    obj.shader->use();

    obj.shader->setVec2("uOffset", obj.transform.x, obj.transform.y);
    obj.shader->setVec2("uScale",  obj.transform.sx, obj.transform.sy);
    obj.shader->setVec4("uColour",  obj.r, obj.g, obj.b, obj.a);

    obj.mesh->draw();
}