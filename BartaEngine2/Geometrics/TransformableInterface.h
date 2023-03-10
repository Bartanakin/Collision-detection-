#pragma once
#include"Vector2f.h"
#include "../BartaShapes/Circle.h"

namespace Barta{
	class TransformableInterface{
	public:
		TransformableInterface() = default;
		virtual ~TransformableInterface() = default;

		virtual Vector2f getPosition() const = 0;
		
		virtual void setPosition(Vector2f position) = 0;

		virtual Circle&& getTransformedCircle( const Circle& circle ) const = 0;

		virtual void move( Vector2f shift ) = 0;
	};
}

