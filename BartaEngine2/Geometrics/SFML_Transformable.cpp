#include "SFML_Transformable.h"

Barta::SFML_Transformable::SFML_Transformable()
: transformable(new sf::Transformable) {}

Barta::SFML_Transformable::SFML_Transformable( const SFML_Transformable& second )
: transformable(new sf::Transformable(*second.transformable)) {}

Barta::SFML_Transformable::~SFML_Transformable(){
	delete this->transformable;
}

Barta::Vector2f Barta::SFML_Transformable::getPosition() const {
	return Vector2f(this->transformable->getPosition());
}

void Barta::SFML_Transformable::setPosition( Vector2f position ){
	this->transformable->setPosition( sf::Vector2f( position.getX(), position.getY() ) );
}


Barta::Circle&& Barta::SFML_Transformable::getTransformedCircle( const Circle& circle ) const{
	auto xd0 = std::move( Circle(
		circle.getRadius(),
		Vector2f( this->transformable->getTransform().transformPoint( circle.getCenter().getX(), circle.getCenter().getY() ) )
	) );	// Compiler bug without this line

	return std::move( Circle(
		circle.getRadius(),
		Vector2f( this->transformable->getTransform().transformPoint( circle.getCenter().getX(), circle.getCenter().getY() ) )
	) );
}

void Barta::SFML_Transformable::move( Vector2f shift ){
	this->transformable->move( shift.getX(), shift.getY() );
}
