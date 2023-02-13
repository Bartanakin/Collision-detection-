#pragma once
#include"HitboxInterface.h"
#include"../Geometrics/TransformableInterface.h"

namespace Barta{

	class CircleHitbox final : public HitboxInterface{
	public:
		CircleHitbox( const Circle& circle );
		~CircleHitbox() = default;

		bool isWithin( Vector2f position ) const override;

		bool intersects( const HitboxInterface& secondHitbox, const CollisionDetectionStrategyInterface& collisionDetector ) const override;

		std::unique_ptr<const HitboxInterface> getTransformedHitbox( const TransformableInterface& transformable ) const override;
		
		const Circle& getCircle() const override;

	protected:
		bool intersectsWithCircle( const HitboxInterface& secondHitbox, const CollisionDetectionStrategyInterface& collisionDetector ) const override;

	private:
		Circle circle;
	};

}
