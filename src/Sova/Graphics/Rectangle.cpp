//
// Created by connor on 7/29/18.
//

#include <Sova/Internal/InternalApp.h>
#include <Sova/Graphics/Internal/InternalCamera.h>
#include <Sova/Graphics/Internal/InternalRectangleDrawer.h>
#include <Sova/Math/Math.h>
#include "Rectangle.h"

namespace Sova
{
    Rectangle::Rectangle(int width, int height)
    {
        this->size = New<Point>(width, height);
    }

    void Rectangle::drawSelf(Ref<Camera> camera, int xoffset, int yoffset)
    {
        InternalRectangleDrawer::getInstance()->draw(this, camera->getInternalCamera(), xoffset, yoffset);

        if (this->lineWidth > 0)
        {
            initLines();

            int topLeftX = Math::Min(this->position->x, this->position->x + this->size->x) + 1;
            int topLeftY = Math::Min(this->position->y, this->position->y + this->size->y);
            int bottomRightX = Math::Max(this->position->x, this->position->x + this->size->x);
            int bottomRightY = Math::Max(this->position->y, this->position->y + this->size->y) - 1;

            //int ax = topLeftX;     int ay = topLeftY;
            //int bx = bottomRightX;    int by = ay;
            //int cx = ax;                    int cy = bottomRightY;
            //int dx = bx;                    int dy = cy;

            topLine->setLineStyle(this->lineWidth, this->lineColor, this->lineAlpha);
            topLine->position->set(topLeftX, topLeftY);
            topLine->endPosition->set(bottomRightX-1, topLeftY);

            leftLine->setLineStyle(this->lineWidth, this->lineColor, this->lineAlpha);
            leftLine->position->set(topLeftX, topLeftY);
            leftLine->endPosition->set(topLeftX, bottomRightY+1);

            bottomLine->setLineStyle(this->lineWidth, this->lineColor, this->lineAlpha);
            bottomLine->position->set(topLeftX, bottomRightY);
            bottomLine->endPosition->set(bottomRightX, bottomRightY);

            rightLine->setLineStyle(this->lineWidth, this->lineColor, this->lineAlpha);
            rightLine->position->set(bottomRightX, topLeftY);
            rightLine->endPosition->set(bottomRightX, bottomRightY);

            topLine->drawSelf(camera, xoffset, yoffset);
            leftLine->drawSelf(camera, xoffset, yoffset);
            rightLine->drawSelf(camera, xoffset, yoffset);
            bottomLine->drawSelf(camera, xoffset, yoffset);
        }
    }

    void Rectangle::initLines()
    {
        if (topLine == nullptr || bottomLine == nullptr || leftLine == nullptr || rightLine == nullptr)
        {
            topLine = New<Line>();
            bottomLine = New<Line>();
            leftLine = New<Line>();
            rightLine = New<Line>();
        }
    }
}