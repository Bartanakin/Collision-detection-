#pragma once
#include "../Color.h"
#include "../../Geometrics/Vector2f.h"

namespace Barta{
    class SpriteBuilder {
        public:
        SpriteBuilder() noexcept = default;
        ~SpriteBuilder() noexcept = default;

        SpriteBuilder* setColor1(Color color) { this->color1 = color; return this; }
        SpriteBuilder* setColor2(Color color) { this->color2 = color; return this; }
        SpriteBuilder* setColor3(Color color) { this->color3 = color; return this; }
        SpriteBuilder* setColor4(Color color) { this->color4 = color; return this; }

        SpriteBuilder* setVertex1(Vector2f vertex) { this->vertex1 = vertex; return this; }
        SpriteBuilder* setSize(Vector2f size) { this->size = size; return this; }
        
        protected:
        Color color1;
        Color color2;
        Color color3;
        Color color4;

        Vector2f vertex1;

        Vector2f size;
    };
}

