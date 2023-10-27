#include "Ball.h"
#include "BartaGraph.h"
#include "Hitbox/CircleHitbox.h"
#include <Graphics/SpriteBuilder/CircleSprite.h>

constexpr const std::array<float, 4> Ball::ballSizes = { 10.f, 20.f, 40.f, 80.f };

Ball::Ball(
    Barta::Vector2f initialPosition,
    Barta::DynamicsDTO initialDynamics,
    BallSize size
) :
    transformable(std::move(BartaGraph::createNewTransformableInstance())),
    hitbox(new Barta::CircleHitbox(Barta::Circle(
        Ball::ballSizes[static_cast<size_t>(size)],
        Barta::Vector2f(Ball::ballSizes[static_cast<size_t>(size)], Ball::ballSizes[static_cast<size_t>(size)])
    ))),
    dynamicsDTO(std::move(initialDynamics)),
    resource({0})
{
    auto merger = Barta::SpriteMerger();
    merger.addCircleSprite(Barta::CircleSprite(
        Barta::Circle(
            Ball::ballSizes[static_cast<size_t>(size)],
            Barta::Vector2f(Ball::ballSizes[static_cast<size_t>(size)], Ball::ballSizes[static_cast<size_t>(size)])
        ),
        Barta::Color(255, 0, 0, 255)
    ));
    this->resource = merger.merge(false);

    this->transformable->setPosition(initialPosition);
}

bool Ball::isToBeDeleted() const{
    return false;
}

const Barta::TransformableInterface& Ball::getTransformable() const{
    return *this->transformable;
}

const Barta::BartaSprite* Ball::getResource() noexcept{
    return &this->resource;
}

std::unique_ptr<const Barta::HitboxInterface> Ball::getHitbox() const{
    return this->hitbox->getTransformedHitbox( *this->transformable );
}

void Ball::move( const Barta::Vector2f& shift ){
    this->transformable->move( shift );
}

const Barta::DynamicsDTO& Ball::getDynamicsDTO() const{
    return this->dynamicsDTO;
}

void Ball::setDynamicsDTO( const Barta::DynamicsDTO& dynamicsDTO  ){
    this->dynamicsDTO = dynamicsDTO;
}
