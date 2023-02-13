#pragma once
#include"SFML/Graphics.hpp"
namespace Barta{
	class Vector2f{
	private:
		float x;
		float y;
	public:
		Vector2f( float x, float y );
		Vector2f( const Vector2f& second );
		Vector2f( sf::Vector2f vector );
		float getX() const;
		float getY() const;

		Vector2f&& operator*( float scalar ) const;

		float operator*( const Vector2f& ) const;

		Vector2f operator-( const Vector2f& ) const;

		float squareOfDistance( const Vector2f& ) const;
	};
}

