//
// Created by barta on 27/12/2023.
//

#include "Button.h"
#include "BartaGraph.h"
#include "Graphics/SpriteBuilder/RectangleWithColorsSpriteBuilder.h"
#include "Graphics/SpriteBuilder/StringSpriteBuilder.h"
#include "Hitbox/AABB_Hitbox.h"

Button::Button(
    Barta::Vector2f position,
    Barta::Vector2f testTranslation,
    Barta::Vector2f size,
    std::string string
)
    : transformable(std::move(BartaGraph::createNewTransformableInstance())),
      hitbox(new Barta::AABB_Hitbox(Barta::AABB(
          {0.f, 0.f},
          size
          ))),
      isMouseHover(false),
      resource(0),
      hoveredResource(0)
{
    auto merger = Barta::SpriteMerger();

    auto builder = Barta::RectangleWithColorsSpriteBuilder();
    builder.setAllColors(Barta::Color(100, 100, 100));
    builder.setVertex1({0.f, 0.f});
    builder.setSize(size);
    auto rectangleSprite = builder.build();

    builder.setAllColors(Barta::Color(156, 128, 70));
    auto hoveredRectangleSprite = builder.build();

    auto stringBuilder = Barta::StringSpriteBuilder();
    stringBuilder.setVertex1(testTranslation);
    stringBuilder.setFontSize(15);
    stringBuilder.setString(std::move(string));
    auto stringSprite = stringBuilder.build();

    merger.addRectanglewithColors(rectangleSprite);
    merger.addString(stringBuilder.build());
    this->resource = merger.merge(false);

    merger.addRectanglewithColors(hoveredRectangleSprite);
    merger.addString(stringBuilder.build());
    this->hoveredResource = merger.merge(false);

    this->transformable->setPosition(position);
}

bool Button::isToBeDeleted() const {
    return Barta::DeletableObject::isToBeDeleted();
}
const Barta::TransformableInterface &Button::getTransformable() const {
    return *this->transformable;
}
const Barta::BartaSprite *Button::getResource() noexcept {
    if (this->isMouseHover) {
        return &this->hoveredResource;
    } else {
        return &this->resource;
    }
}
int Button::getZIndex() const {
    return 5;
}
std::unique_ptr<const Barta::HitboxInterface> Button::getHitbox() const {
    return this->hitbox->getTransformedHitbox( *this->transformable );
}
void Button::setIsMouseHover(bool isMouseHover) {
    this->isMouseHover = isMouseHover;
}
