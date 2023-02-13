#include "Vector2f.h"

Barta::Vector2f::Vector2f( float x, float y ) : x( x ), y( y ){}

Barta::Vector2f::Vector2f( const Vector2f& second ) : x( second.x ), y( second.y ){}

Barta::Vector2f::Vector2f( sf::Vector2f vector ) : x( vector.x ), y( vector.y ){}

float Barta::Vector2f::getX() const{
	return this->x;
}

float Barta::Vector2f::getY() const{
	return this->y;
}

Barta::Vector2f&& Barta::Vector2f::operator*( float scalar ) const{
	return std::move( Vector2f( scalar * this->x, scalar * this->y ) );
}

float Barta::Vector2f::operator*( const Vector2f& second ) const{
	return this->getX() * second.getX() + this->getY() * second.getY();
}

Barta::Vector2f Barta::Vector2f::operator-( const Vector2f& second ) const{
	return Vector2f( this->getX() - second.getX(), this->getY() - second.getY() );
}

float Barta::Vector2f::squareOfDistance( const Vector2f& second ) const{
	auto AminusB =  *this - second;

	return ( AminusB ) * ( AminusB );
}
