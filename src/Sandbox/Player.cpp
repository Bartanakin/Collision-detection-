#include "Player.h"
#include "BartaGraph.h"
#include "Hitbox/AABB_Hitbox.h"
#include "SandboxResource.h"

Player::Player(
	Barta::Vector2f initialPosition,
    Barta::DynamicsDTO dynamics,
    Gun* gun
) : 
	transformable(BartaGraph::createNewTransformableInstance()),
	hitbox( new Barta::AABB_Hitbox( Barta::AABB( Barta::Vector2f( 0.f, 0.f ), Barta::Vector2f( 40.f, 60.f ) ) ) ),
    dynamics(dynamics),
    gun(gun),
    resource(Barta::BartaSprite(static_cast<int>(SandboxResource::YELLOW_BLOCK)))
{
	this->setPosition(initialPosition);
}

const Barta::TransformableInterface& Player::getTransformable() const{
	return *this->transformable;
}

const Barta::BartaSprite* Player::getResource() noexcept{
	return &this->resource;
}

std::unique_ptr<const Barta::HitboxInterface> Player::getHitbox() const{
	return std::unique_ptr<const Barta::HitboxInterface>( this->hitbox->getTransformedHitbox( *this->transformable ) );
}

void Player::move( const Barta::Vector2f& shift ){
	this->transformable->move(shift);
    this->gun->move(shift);
}

const Barta::DynamicsDTO& Player::getDynamicsDTO() const{
	return this->dynamics;
}

void Player::setDynamicsDTO( const Barta::DynamicsDTO& dynamics ){
    this->dynamics = dynamics;
}

void Player::setVelocity(Barta::Vector2f velocity) {
    this->dynamics.velocity = velocity;
}
void Player::setPosition(Barta::Vector2f position) {
    this->transformable->setPosition(position);
    this->gun->rotate(-this->gun->getRotation(), this->gun->getDynamicsDTO().massCenter);
    this->gun->setPosition(position + Barta::Vector2f(10.f, 10.f));
}
int Player::getZIndex() const {
    return 2;
}
