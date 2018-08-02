#pragma once

//
// Created by connor on 7/29/18.
//

#include "Container.h"
#include "Color.h"

namespace Sova
{
    class Shape : public Sova::Container {
    public:
        Shape() {};
        void setLineStyle(int lineWidth, Color lineColor, float lineAlpha);
        void setFillStyle(Color fillColor, float fillAlpha);
        void setFillStyle(bool filling);

        Color fillColor = Color::White;
        float fillAlpha = 1.0f;
        float lineAlpha = 1.0f;
        Color lineColor = Color::White;
    private:
        bool filling = true;
    protected:
        int lineWidth = 1;
    };
}