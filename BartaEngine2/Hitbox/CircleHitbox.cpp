#include "CircleHitbox.h"
#include "../Collisions/CheckCollisionVisitors/CircleCircleCheckCollisionVisitor.h"
#include<math.h>
#include<iostream>
#include<memory>

namespace Barta{

	CircleHitbox::CircleHitbox( const Circle& circle ) 
		:circle( circle ){}

	const Circle& CircleHitbox::getCircle() const{
		return this->circle;
	}

	bool CircleHitbox::intersectsWithCircle( const HitboxInterface& secondHitbox, const CollisionDetectionStrategyInterface& collisionDetector ) const{
		return collisionDetector.acceptCheckCollisionVisitor( CircleCircleCheckCollisionVisitor(
			this->getCircle(),
			secondHitbox.getCircle()
		) );
	}

	bool CircleHitbox::isWithin( Vector2f position) const {
		return pow( position.getX() - this->circle.getCenter().getX(), 2 ) + pow( position.getY() - this->circle.getCenter().getY(), 2 )
			<= pow( this->circle.getRadius(), 2 ); ;
	}

	bool CircleHitbox::intersects( const HitboxInterface& secondHitbox, const CollisionDetectionStrategyInterface& collisionDetector ) const{
		return this->intersectsWithCircle(secondHitbox, collisionDetector);
	}

	std::unique_ptr<const HitboxInterface> CircleHitbox::getTransformedHitbox( const TransformableInterface& transformable ) const{
		int xd = 2;		// Compiler bug without this line

		return std::unique_ptr<const HitboxInterface>( new CircleHitbox( transformable.getTransformedCircle( this->circle ) ) );
	}
}
