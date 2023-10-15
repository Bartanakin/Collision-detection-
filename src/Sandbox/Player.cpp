#include "Player.h"
#include "BartaGraph.h"
#include "Hitbox/AABB_Hitbox.h"
#include "SandboxResource.h"

Player::Player(
	Barta::Vector2f initialPosition,
    Barta::DynamicsDTO dynamics,
    Gun* gun
) : 
	transformable( std::move(BartaGraph::createNewTransformableInstance()) ),
	hitbox( new Barta::AABB_Hitbox( Barta::AABB( Barta::Vector2f( 0.f, 0.f ), Barta::Vector2f( 40.f, 60.f ) ) ) ),
    dynamics(dynamics),
    gun(gun)
{
	this->transformable->setPosition(initialPosition);
    this->gun->setPosition(initialPosition + Barta::Vector2f(10.f, 10.f));
}

bool Player::isToBeDeleted() const{
	return false;
}

const Barta::TransformableInterface& Player::getTransformable() const{
	return *this->transformable;
}

int Player::getResourceId() const noexcept{
	return static_cast<int>(SandboxResource::YELLOW_BLOCK);
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
