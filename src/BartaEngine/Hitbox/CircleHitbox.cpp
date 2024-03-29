#include "pch.h"
#include "CircleHitbox.h"
#include "../Collisions/CheckCollisionVisitors/CircleCircleCheckCollisionVisitor.h"
#include "../Collisions/CheckCollisionVisitors/CircleAABBCheckCollisionVisitor.h"

namespace Barta{
	class AABB_Hitbox;

	CircleHitbox::CircleHitbox( const Circle& circle ) 
		:circle( circle ){}

	const Circle& CircleHitbox::getCircle() const{
		return this->circle;
	}

	CollisionTestResult CircleHitbox::intersectsWithCircle(
		const Circle& secondCircle,
		const CollisionDetectionStrategyInterface& collisionDetector,
		const DynamicsDTO& dynamicsDifference
	)  const{
		return collisionDetector.acceptCheckCollisionVisitor( CircleCircleCheckCollisionVisitor(
			secondCircle,
			this->getCircle(),
			dynamicsDifference
		) );
	}

	CollisionTestResult CircleHitbox::intersectsWithAABB(
		const AABB& secondAABB,
		const CollisionDetectionStrategyInterface& collisionDetector,
		const DynamicsDTO& dynamicsDifference
	) const{
		return collisionDetector.acceptCheckCollisionVisitor( CircleAABBCheckCollisionVisitor(
			this->getCircle(),
			secondAABB,
			-dynamicsDifference
		) );
	}

	bool CircleHitbox::isWithin( const Vector2f& position ) const {
		return pow( position.getX() - this->circle.getCenter().getX(), 2 ) + pow( position.getY() - this->circle.getCenter().getY(), 2 )
			<= pow( this->circle.getRadius(), 2 ); ;
	}

	CollisionTestResult CircleHitbox::intersects(
		const HitboxInterface& secondHitbox,
		const CollisionDetectionStrategyInterface& collisionDetector,
		const DynamicsDTO& dynamicsDifference
	)  const{
		return secondHitbox.intersectsWithCircle( this->getCircle(), collisionDetector, dynamicsDifference );
	}

	std::unique_ptr<const HitboxInterface> CircleHitbox::getTransformedHitbox( const TransformableInterface& transformable ) const{
		return std::unique_ptr<const HitboxInterface>( new CircleHitbox( transformable.getTransformedCircle( this->circle ) ) );
	}
}
