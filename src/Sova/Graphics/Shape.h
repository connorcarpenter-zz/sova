#pragma once

//
// Created by connor on 7/29/18.
//

#include "Container.h"
#include "Color.h"

namespace Sova
{
    class Shape : public Sova::Container {
    protected:
        Color fillColor = Color::White;
        float fillAlpha = 1.0f;
    public:
        Shape() {};
        void setLineStyle(int lineWidth, Color lineColor, float lineAlpha);
        void setFillStyle(Color fillColor, float fillAlpha);
        void setFillStyle(bool filling);
    private:
        int lineWidth = 1;
        Color lineColor = Color::White;
        float lineAlpha = 1.0f;
        bool filling = true;
    };
}
