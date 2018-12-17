//
// Created by connor on 12/15/18.
//

#include <algorithm>
#include <Sova/Graphics/Internal/InternalCamera.h>
#include "InternalDrawer.h"

namespace Sova {

    InternalDrawer::InternalDrawer()
    {
    }

    InternalDrawer::~InternalDrawer()
    {
    }

    void InternalDrawer::begin() {
        _renderBatches.clear();

        // Makes _glpyhs.size() == 0, however it does not free internal memory.
        // So when we later call emplace_back it doesn't need to internally call new.
        _glyphs.clear();
    }

    void InternalDrawer::end() {
        // Set up all pointers for fast sorting
        _glyphPointers.resize(_glyphs.size());
        for (int i = 0; i < _glyphs.size(); i++) {
            _glyphPointers[i] = &_glyphs[i];
        }

        createRenderBatches();
    }

    void InternalDrawer::draw(float x0, float y0, float x1, float y1, float u0, float v0, float u1, float v1, float rxskew,
                                  Oryol::Id textureId, Sova::Color color, float alpha) {
        _glyphs.emplace_back(x0, y0, x1, y1, u0, v0, u1, v1, rxskew,
                             textureId, color, alpha);
    }

    void InternalDrawer::render(InternalCamera *internalCamera)
    {
        Oryol::DrawState drawState = internalCamera->getDrawState(); //for some reason, copying the DrawState is necessary before using it... perhaps it's because only one DrawState can be used at a time

        for (size_t i = 0; i < _renderBatches.size(); i++)
        {
            drawState.FSTexture[0] =  _renderBatches[i].textureId;
            Oryol::Gfx::UpdateVertices(drawState.Mesh[0],
                                       _renderBatches[i].vertices.data(),
                                       (int) _renderBatches[i].vertices.size() * sizeof(Vertex));
            Oryol::Gfx::ApplyDrawState(drawState);
            Oryol::Gfx::Draw(Oryol::PrimitiveGroup(0, _renderBatches[i].vertices.size()), 1);
        }
    }

    void InternalDrawer::createRenderBatches() {

        // Resize the buffer to the exact size we need so we can treat
        // it like an array
        if (_glyphPointers.empty()) {
            return;
        }

        //Add the first batch

        _renderBatches.emplace_back(_glyphPointers[0]->textureId);
        _renderBatches.back().vertices.push_back(_glyphPointers[0]->topLeft);
        _renderBatches.back().vertices.push_back(_glyphPointers[0]->bottomLeft);
        _renderBatches.back().vertices.push_back(_glyphPointers[0]->bottomRight);
        _renderBatches.back().vertices.push_back(_glyphPointers[0]->bottomRight);
        _renderBatches.back().vertices.push_back(_glyphPointers[0]->topRight);
        _renderBatches.back().vertices.push_back(_glyphPointers[0]->topLeft);

        //Add all the rest of the glyphs
        for (int cg = 1; cg < _glyphPointers.size(); cg++) {

            // Check if this glyph can be part of the current batch
            if (_glyphPointers[cg]->textureId != _glyphPointers[cg - 1]->textureId) {
                // Make a new batch
                _renderBatches.emplace_back(_glyphPointers[cg]->textureId);
            }
            _renderBatches.back().vertices.push_back(_glyphPointers[cg]->topLeft);
            _renderBatches.back().vertices.push_back(_glyphPointers[cg]->bottomLeft);
            _renderBatches.back().vertices.push_back(_glyphPointers[cg]->bottomRight);
            _renderBatches.back().vertices.push_back(_glyphPointers[cg]->bottomRight);
            _renderBatches.back().vertices.push_back(_glyphPointers[cg]->topRight);
            _renderBatches.back().vertices.push_back(_glyphPointers[cg]->topLeft);
        }
    }
}