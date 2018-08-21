//
// Created by connor on 7/8/18.
//

#include <Modules/Gfx/Gfx.h>
#include "Viewport.h"
#include "Internal/InternalViewport.h"

namespace Sova {
    Sova::Viewport::Viewport(int x, int y, int width, int height, Ref<Camera> camera)
    {
        this->position = New<Point>(x, y);
        this->width = width;
        this->height = height;
        this->camera = camera;

        this->internalViewport = new InternalViewport(this);
    }

    Viewport::~Viewport() {
        delete this->internalViewport;
    }

    void Viewport::drawCamera() {
        this->camera->draw(this->position->x, this->position->y);
    }

    void Viewport::drawViewport() {
        // copy offscreen render target into backbuffer
        Oryol::Gfx::ApplyDrawState(this->internalViewport->getDrawState());
        Oryol::Gfx::Draw();
    }

    InternalCamera* Viewport::getInternalCamera() {
        return this->camera->getInternalCamera();
    }


}