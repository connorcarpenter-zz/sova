//
// Created by connor on 7/8/18.
//

#include "Viewport.h"

namespace Sova {
    Sova::Viewport::Viewport(int x, int y, int width, int height, Ref<Camera> camera)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->camera = camera;
    }

    void Viewport::draw() {
        this->camera->draw(ThisRef<Viewport>());
    }
}