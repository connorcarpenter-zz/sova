//
// Created by connor on 12/15/18.
//

#include "Glyph.h"

namespace Sova {

    Glyph::Glyph(float x0, float y0, float x1, float y1, float u0, float v0, float u1, float v1, float rxskew,
                     Oryol::Id TextureId, Sova::Color color, float Alpha) :
            textureId(TextureId),
            alpha(Alpha){

            topLeft.setColor(color, alpha);
            topLeft.setPosition(x0 + rxskew, y0);
            topLeft.setUV(u0, v0);

            bottomLeft.setColor(color, alpha);
            bottomLeft.setPosition(x0, y1);
            bottomLeft.setUV(u0, v1);

            bottomRight.setColor(color, alpha);
            bottomRight.setPosition(x1, y1);
            bottomRight.setUV(u1, v1);

            topRight.setColor(color, alpha);
            topRight.setPosition(x1 + rxskew, y0);
            topRight.setUV(u1, v0);
    }
}