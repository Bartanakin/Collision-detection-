#include "ReloadMarker.h"
#include "BartaGraph.h"
#include <Graphics/SpriteBuilder/RectangleWithColorsSpriteBuilder.h>
#include <Graphics/SpriteBuilder/SpriteMerger.h>

ReloadMarker::ReloadMarker(
    Gun* gun
) noexcept :
	transformable(std::move(BartaGraph::createNewTransformableInstance())),
    resource({0}),
    gun(gun)
{
    this->loadResource();

    this->transformable->setPosition({200.f, 630.f});
}

const Barta::TransformableInterface &ReloadMarker::getTransformable() const {
    return *this->transformable;
}

const Barta::BartaSprite *ReloadMarker::getResource() noexcept {
    this->loadResource();

    return &this->resource;
}

void ReloadMarker::loadResource() {
    float reloadRatio = std::max({
        std::min({
            1.f,
            static_cast<float>((Gun::reloadTime - this->gun->getLeftToReload()).count()) / static_cast<float>(Gun::reloadTime.count())
        }),
        0.f
    });
    auto color1 = Barta::Color(0, 0, 0, 255);
    auto color2 = Barta::Color(
        static_cast<unsigned char>(255 * reloadRatio),
        static_cast<unsigned char>(255 * reloadRatio),
        static_cast<unsigned char>(255 * reloadRatio),
        255
    );
    auto builder = Barta::RectangleWithColorsSpriteBuilder();
    builder.setVertex1({0.f, 0.f});
    builder.setSize({100.f * reloadRatio, 20.f});
    builder.setColor1(color1);
    builder.setColor2(color1);
    builder.setColor3(color2);
    builder.setColor4(color2);

    auto merger = Barta::SpriteMerger();
    merger.addRectanglewithColors(builder.build());

    this->resource = merger.merge(false);
}
int ReloadMarker::getZIndex() const {
    return 10;
}
