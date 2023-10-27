#pragma once
#include "../../pch.h"
#include "SpriteBuilder.h"
#include "../BartaSprite.h"
#include "RectangleWithColorsSprite.h"
#include "CircleSprite.h"

namespace Barta{
    class SpriteMerger {
        public:
        SpriteMerger() noexcept;

        SpriteMerger* addRectanglewithColors(const RectangleWithColorsSprite& addRectanglewithColors);
        SpriteMerger* addCircleSprite(const CircleSprite& circleSprite);
        
        BartaSprite merge(bool reloadCache);

        protected:

        std::vector<float> data;
        std::vector<SpriteType> types;
    };
}

