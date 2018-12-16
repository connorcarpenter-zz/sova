#pragma once

//
// Created by connor on 12/15/18.
//

#include <Modules/Resource/Id.h>
#include <Sova/Graphics/Color.h>
#include "Vertex.h"

namespace Sova {
    class Glyph {
    public:

        Glyph(float x0, float y0, float x1, float y1, float u0, float v0, float u1, float v1, Oryol::Id TextureId,
                      Sova::Color Color, float Alpha);

        Glyph(float x0, float y0, float x1, float y1, float u0, float v0, float u1, float v1, float rxskew,
                      Oryol::Id TextureId, Sova::Color Color, float Alpha);

        Oryol::Id textureId;
        float alpha;

        Vertex topLeft;
        Vertex bottomLeft;
        Vertex topRight;
        Vertex bottomRight;
    };
}