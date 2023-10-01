#pragma once
#include "../../pch.h"
#include "CollisionTestExecutorInterface.h"

namespace Barta {

	class CollisionTestExecutor:public CollisionTestExecutorInterface {
		public:
		CollisionTestExecutor(std::unique_ptr<CollisionDetectionStrategyInterface> collisionDetectionStrategy) noexcept;
		virtual ~CollisionTestExecutor() noexcept = default;

		virtual ResultsList executeTests(const CollisionAwareInterface::CollidableList& collidableList) override;

		private:

		std::unique_ptr<CollisionDetectionStrategyInterface> collisionDetectionStrategy;
	};

}