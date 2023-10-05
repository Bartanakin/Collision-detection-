#pragma once
#include "../pch.h"

namespace Barta{

	class Vector2f{
	private:
		float x;
		float y;
	public:
	    Vector2f() noexcept = default;
		Vector2f( float x, float y );
		Vector2f( const Vector2f& second );
		Vector2f( sf::Vector2f vector );
        Barta::Vector2f& operator=(const Barta::Vector2f&);
		inline float getX() const { return this->x; }
		inline float getY() const { return this->y; }

		Vector2f operator*(float scalar) const noexcept;

		float operator*( const Vector2f& ) const;

		Vector2f operator-( const Vector2f& ) const;

		Vector2f operator+(const Vector2f&) const;

		bool operator==( const Vector2f& ) const;

		float squareOfDistance( const Vector2f& ) const;

		Vector2f perpendicular() const;

		Vector2f normalised() const;
	};

	std::ostream& operator << ( std::ostream&, const Vector2f& );
}
