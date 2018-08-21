//
// Created by connor on 7/29/18.
//

#include <Sova/Internal/InternalApp.h>
#include <Sova/Graphics/Internal/InternalCamera.h>
#include <Sova/Graphics/Internal/InternalPixelDrawer.h>
#include "Pixel.h"

namespace Sova
{
    void Pixel::drawSelf(Ref<Camera> camera, int xoffset, int yoffset)
    {
        InternalPixelDrawer::getInstance()->draw(this, camera->getInternalCamera(), xoffset, yoffset);
    }

}