#include "Ball.h"
#include "BartaGraph.h"
#include "Hitbox/CircleHitbox.h"
#include <iterator>

const std::function<float(Ball::BallSize)> Ball::ballSize
    = [] (Ball::BallSize n) constexpr { return 10.f * static_cast<float>(1 << (static_cast<int>(n) - 1)); };

const std::function<float(Ball::BallSize)> Ball::velocity
    = [] (Ball::BallSize n) constexpr { return 200.f * std::pow<float>(1.15f, static_cast<float>(n)); };

const std::function<float(Ball::BallSize)> Ball::mass
    = [] (Ball::BallSize n) constexpr { return 0.25f * static_cast<float>(n); }; 

constexpr const float Ball::horizontalSpeed = 25.f;

Ball::Ball(
    Barta::Vector2f initialPosition,
    bool movingLeft,
    BallSize size
) :
    transformable(std::move(BartaGraph::createNewTransformableInstance())),
    hitbox(new Barta::CircleHitbox(Barta::Circle(
        Ball::ballSize(size),
        Barta::Vector2f(Ball::ballSize(size), Ball::ballSize(size))
    ))),
    dynamicsDTO(
        {(movingLeft * (-1) + !movingLeft) * Ball::horizontalSpeed, Ball::velocity(size)},
        false,
        Ball::mass(size),
        Constants::GRAVITY
    ),
    size(size),
    resource({0})
{
//    std::cout << Ball::ballSize(size) << std::endl;
    auto merger = Barta::SpriteMerger();
    merger.addCircleSprite(Barta::CircleSprite(
        Barta::Circle(
            Ball::ballSize(size),
            Barta::Vector2f(Ball::ballSize(size), Ball::ballSize(size))
        ),
        Barta::Color(255, 0, 0, 255)
    ));
    this->resource = merger.merge(false);

    this->transformable->setPosition(initialPosition);
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

void Ball::setDynamicsDTO(const Barta::DynamicsDTO& dynamicsDTO){
    this->dynamicsDTO = dynamicsDTO;
}

float Ball::getRebounceVelocity() const {
    return Ball::velocity(this->size);
}

Ball::BallSize Ball::getSize() const {
    return this->size;
}
int Ball::getZIndex() const {
    return 1;
}

Ball::BallSize& operator--(Ball::BallSize& ballSize) {
    if (ballSize == Ball::BallSize::VERY_SMALL) {
        throw "Cannot decrement BallSize lower that VERY_SMALL!";
    }

    ballSize = static_cast<Ball::BallSize>(static_cast<int>(ballSize) - 1);

    return ballSize;
}
