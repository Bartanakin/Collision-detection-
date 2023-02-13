#pragma once
#include "../Collisions/CollisionDetectionStrategyInterface.h"
#include "../Geometrics/TransformableInterface.h"

namespace Barta{
	class HitboxInterface{
	public:
		HitboxInterface() = default;
		virtual ~HitboxInterface() = default;

		virtual bool isWithin( Vector2f position ) const = 0;

		virtual bool intersects( const HitboxInterface& secondHitbox, const CollisionDetectionStrategyInterface& collisionDetector ) const = 0;

		virtual std::unique_ptr<const HitboxInterface> getTransformedHitbox( const TransformableInterface& transformable ) const = 0;

		virtual const Circle& getCircle() const = 0;

	protected:
		virtual bool intersectsWithCircle( const HitboxInterface& secondHitbox, const CollisionDetectionStrategyInterface& collisionDetector ) const = 0;
	};
}
