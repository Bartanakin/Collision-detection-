#pragma once
#include "../../pch.h"
#include "CollisionTestExecutorDecorator.h"

namespace Barta {

	class FilterCollisionsOvertimeDecorator:public CollisionTestExecutorDecorator {
		public:

		FilterCollisionsOvertimeDecorator(
			std::unique_ptr<CollisionTestExecutorInterface> decoratedObject,
			TimerInterface& timer
		) noexcept;

		virtual ResultsList executeTests(const CollisionAwareInterface::CollidableList& collidableList) override;

		private:

		constexpr const static float collisionTestError = 0.0001f;
		TimerInterface& timer;
        ExtendedCollisionResult lastCollisionResult;
	};

}