//
// Created by connor on 7/29/18.
//

#include "Shape.h"

namespace Sova
{

    void Shape::setLineStyle(int lineWidth, Color lineColor, float lineAlpha) {
        this->lineWidth = lineWidth;
        this->lineColor = lineColor;
        this->lineAlpha = lineAlpha;
        this->lines = true;
    }

    void Shape::setLineStyle(bool lines) {
        if (lines)
        {
            this->setLineStyle(1, Color::White, 1);
            this->lines = true;
        }
        else
        {
            this->lines = false;
        }
    }

    void Shape::setFillStyle(Color fillColor, float fillAlpha) {
        this->filling = true;
        this->fillColor = fillColor;
        this->fillAlpha = fillAlpha;
    }

    void Shape::setFillStyle(bool filling) {
        if (filling)
        {
            this->setFillStyle(Color::White, 1);
            this->filling = true;
        }
        else
        {
            this->filling = false;
        }
    }
}