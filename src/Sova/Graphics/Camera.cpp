//
// Created by connor on 7/8/18.
//

#include <Modules/Gfx/Gfx.h>
#include <Sova/Internal/InternalApp.h>
#include "Camera.h"
#include "Container.h"
#include "Internal/InternalCamera.h"
#include "Rectangle.h"

namespace Sova
{
    Sova::Camera::Camera(int x, int y, int width, int height, Ref <Container> target, Color bckColor, float bckAlpha, bool drawTarget,
                             bool autoRedraw) : Refable()
    {
        this->position = New<Point>(x, y);
        this->width = width;
        this->height = height;
        this->target = target;
        this->drawTarget = drawTarget;
        this->autoRedraw = autoRedraw;
        this->backgroundColor = bckColor;
        this->backgroundAlpha = bckAlpha;

        this->internalCamera = new InternalCamera(this);
    }

    Camera::~Camera() {
        delete this->internalCamera;
    }

    void Sova::Camera::draw(int xoffset, int yoffset)
    {
        if (!this->drawTarget) return;
        if (skipFrames != 0)
        {
            skipFrames -= 1;
            return;
        }
        else
        {
            skipFrames = SkipFramesToDrawFramesRatio;
        }

        Oryol::Gfx::BeginPass(this->internalCamera->getCanvasPass());
        InternalApp::getInternalApp()->drawer->begin();
        this->target->Draw(ThisRef<Camera>(), xoffset - this->position->x, yoffset - this->position->y);
        InternalApp::getInternalApp()->drawer->end();
        InternalApp::getInternalApp()->drawer->render(this->internalCamera);
        Oryol::Gfx::EndPass();
    }

    InternalCamera *Camera::getInternalCamera() {
        return this->internalCamera;
    }

    void Camera::clearCamera() {

        auto clearRect = New<Sova::Rectangle>(0,0);
        clearRect->size->set(this->width, this->height);
        clearRect->setFillStyle(this->backgroundColor, this->backgroundAlpha);
        clearRect->setLineStyle(1, Color::Black, 1);

        Oryol::Gfx::BeginPass(this->internalCamera->getCanvasPass());
        auto thisCamera = ThisRef<Camera>();
        clearRect->drawSelf(thisCamera, 0, 0);
        Oryol::Gfx::EndPass();
    }
}
