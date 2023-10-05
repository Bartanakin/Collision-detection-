#include "Ball.h"
#include "BartaGraph.h"
#include "Hitbox/CircleHitbox.h"


Ball::Ball( Barta::Vector2f initialPosition, Barta::DynamicsDTO initialDynamics ) :
    transformable( std::move(BartaGraph::createNewTransformableInstance()) ),
    hitbox( new Barta::CircleHitbox( Barta::Circle( 40.f, Barta::Vector2f( 40.f, 40.f ) ) ) ),
    dynamicsDTO( std::move( initialDynamics )),
    ballColor( Barta::Resource::RED_BALL )
{
    this->transformable->setPosition( initialPosition );
}

bool Ball::isToBeDeleted() const{
    return false;
}

const Barta::TransformableInterface& Ball::getTransformable() const{
    return *this->transformable;
}

Barta::Resource Ball::getResourceId() const noexcept{
    return this->ballColor;
}

Barta::Resource Ball::getBallCollor() const{
    return this->ballColor;
}

void Ball::setBallCollor( Barta::Resource resource ){
    this->ballColor = resource;
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
