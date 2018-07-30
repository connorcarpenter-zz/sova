//
// Created by connor on 7/29/18.
//

#include <Sova/Internal/InternalApp.h>
#include <Sova/Graphics/Internal/InternalCamera.h>
#include <Sova/Graphics/Internal/InternalLineDrawer.h>
#include "Line.h"

namespace Sova
{
    Line::Line()
    {
        this->endPosition = New<Point>(0,0);
    }

    void Line::drawSelf(Ref<Camera> camera, int xoffset, int yoffset)
    {
        InternalLineDrawer::getInstance()->draw(this, camera->getInternalCamera(), xoffset, yoffset);
    }

}