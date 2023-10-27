#include "SpriteMerger.h"

Barta::SpriteMerger::SpriteMerger() noexcept :
    data({}),
    types({})
{}

Barta::SpriteMerger *Barta::SpriteMerger::addRectanglewithColors(
    const RectangleWithColorsSprite &addRectanglewithColors
) {
    this->types.push_back(SpriteType::RECTABGLE_WITH_COLORS);

    for (const auto& vector : {
        addRectanglewithColors.aabb.getLeftTop(),
        addRectanglewithColors.aabb.getWidthHeight(),
    }) {
        this->data.push_back(vector.getX());
        this->data.push_back(vector.getY());
        this->data.push_back(0.f);
    }

    for (const auto& color : {
        addRectanglewithColors.leftTopColor,
        addRectanglewithColors.rightTopColor,
        addRectanglewithColors.rightBottomColor,
        addRectanglewithColors.leftBottomColor
    }) {
        this->data.push_back(color.r);
        this->data.push_back(color.g);
        this->data.push_back(color.b);
        this->data.push_back(color.a);
    }

    return this;
}

Barta::SpriteMerger* Barta::SpriteMerger::addCircleSprite(const CircleSprite & circleSprite) {
    this->types.push_back(SpriteType::CIRCLE);

    this->data.push_back(circleSprite.circle.getCenter().getX());
    this->data.push_back(circleSprite.circle.getCenter().getY());
    this->data.push_back(0.f);
    this->data.push_back(circleSprite.circle.getRadius());

    this->data.push_back(circleSprite.color.r);
    this->data.push_back(circleSprite.color.g);
    this->data.push_back(circleSprite.color.b);
    this->data.push_back(circleSprite.color.a);

    return this;
}

Barta::BartaSprite Barta::SpriteMerger::merge(bool reloadCache) {
    auto sprite = BartaSprite(
        reloadCache,
        std::move(this->data),
        std::move(this->types)
    );

    this->data = {};
    this->types = {};

    return sprite;
}
