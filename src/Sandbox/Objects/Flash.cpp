//
// Created by barta on 01/01/2024.
//

#include "Flash.h"
#include "BartaGraph.h"
#include "Graphics/SpriteBuilder/StringSpriteBuilder.h"
Flash::Flash(
    Barta::Vector2f position
)   : transformable(std::move(BartaGraph::createNewTransformableInstance())),
      resource(0),
      until(std::chrono::steady_clock::now()),
      emptyResource(0)
{
    this->transformable->setPosition(position);
    this->emptyResource = this->createResource("");
}

bool Flash::isToBeDeleted() const {
    return Barta::DeletableObject::isToBeDeleted();
}

const Barta::TransformableInterface &Flash::getTransformable() const {
    return *this->transformable;
}

const Barta::BartaSprite *Flash::getResource() noexcept {
    if (this->until < std::chrono::steady_clock::now()) {
        return &this->emptyResource;
    }

    return &this->resource;
}

int Flash::getZIndex() const {
    return 6;
}

Barta::BartaSprite Flash::createResource(std::string message) {
    auto merger = Barta::SpriteMerger();

    auto stringBuilder = Barta::StringSpriteBuilder();
    stringBuilder.setVertex1(this->transformable->getPosition());
    stringBuilder.setFontSize(20);
    stringBuilder.setString(message);
    auto stringSprite = stringBuilder.build();

    merger.addString(stringBuilder.build());

    return merger.merge(false);
}

void Flash::setMessage(std::string message, std::chrono::seconds seconds) {
    this->resource = this->createResource(std::move(message));
    this->until = std::chrono::steady_clock::now() + seconds;
}
