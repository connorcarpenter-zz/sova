#pragma once

//
// Created by connor on 12/15/18.
//

#include <Sova/Graphics/Color.h>

namespace Sova {
    struct Position {
        float x;
        float y;
    };

    struct ColorRGBA8 {
        ColorRGBA8() : r(0), g(0), b(0), a(0) { }
        ColorRGBA8(float R, float G, float B, float A) :
                r(R), g(G), b(B), a(A) { }
        float r;
        float g;
        float b;
        float a;
    };

    struct UV {
        float u;
        float v;
    };

    //The vertex definition
    struct Vertex {
        //This is the position struct. When you store a struct or class
        //inside of another struct or class, it is called composition. This is
        //layed out exactly the same in memory as if we had a float position[2],
        //but doing it this way makes more sense.
        Position position;

        //UV texture coordinates.
        UV uv;

        //4 bytes for r g b a color.
        ColorRGBA8 color;

        void setPosition(float x, float y) {
            position.x = x;
            position.y = y;
        }

        void setColor(float r, float g, float b, float a) {
            color.r = r;
            color.g = g;
            color.b = b;
            color.a = a;
        }

        void setColor(Sova::Color otherColor, float alpha) {
            color.r = ((float) otherColor.red) / 255;
            color.g = ((float) otherColor.green) / 255;
            color.b = ((float) otherColor.blue) / 255;
            color.a = alpha;
        }

        void setUV(float u, float v) {
            uv.u = u;
            uv.v = v;
        }
    };
}