#pragma once

//
// Created by connor on 12/15/18.
//

#include <Modules/Resource/Id.h>
#include "Vertex.h"

namespace Sova {
    class RenderBatch {
    public:
        RenderBatch(Oryol::Id TextureId) : textureId(TextureId) {
        }
        std::vector <Vertex> vertices;
        Oryol::Id textureId;
    };
}