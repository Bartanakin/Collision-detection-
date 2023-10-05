#include "pch.h"
#include "SFML_Transformable.h"

Barta::SFML_Transformable::SFML_Transformable()
: transformable(std::make_unique<sf::Transformable>()) {}

Barta::SFML_Transformable::SFML_Transformable(const SFML_Transformable& second)
: transformable(std::make_unique<sf::Transformable>(*second.transformable)) {}

Barta::Vector2f Barta::SFML_Transformable::getPosition() const {
	return Vector2f(this->transformable->getPosition());
}

void Barta::SFML_Transformable::setPosition( Vector2f position ){
	this->transformable->setPosition( sf::Vector2f( position.getX(), position.getY() ) );
}


Barta::Circle Barta::SFML_Transformable::getTransformedCircle( const Circle& circle ) const{
	return Circle(
		circle.getRadius(),
		Vector2f( this->transformable->getTransform().transformPoint( circle.getCenter().getX(), circle.getCenter().getY() ) )
	);
}

void Barta::SFML_Transformable::move( Vector2f shift ){
	this->transformable->move( shift.getX(), shift.getY() );
}

Barta::AABB Barta::SFML_Transformable::getTransformedAABB( const AABB& aabb ) const{
	return AABB(
		Vector2f( this->transformable->getTransform().transformPoint( aabb.getLeftTop().getX(), aabb.getLeftTop().getY() ) ),
		aabb.getWidthHeight()
	);
}
