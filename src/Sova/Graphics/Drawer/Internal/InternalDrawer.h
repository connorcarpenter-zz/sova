#pragma once

//
// Created by connor on 12/15/18.
//

#include <Sova/Graphics/Color.h>
#include <vector>
#include <Sova/Graphics/Internal/InternalCamera.h>
#include "RenderBatch.h"
#include "Glyph.h"

namespace Sova {
    class InternalDrawer
    {
    public:
        InternalDrawer();
        ~InternalDrawer();

        // Begins the InternalDrawer
        void begin();

        // Ends the InternalDrawer
        void end();

        // Adds a glyph to the InternalDrawer

        void draw(float x0, float y0, float x1, float y1, float u0, float v0, float u1, float v1, float rxskew,
                          Oryol::Id textureId, Sova::Color color, float alpha);

        // Renders the entire InternalDrawer to the screen
        void render(InternalCamera *internalCamera);

    private:
        // Creates all the needed RenderBatches
        void createRenderBatches();

        std::vector<Glyph*> _glyphPointers; ///< This is for sorting
        std::vector<Glyph> _glyphs; ///< These are the actual glyphs
        std::vector<RenderBatch> _renderBatches;
    };
}