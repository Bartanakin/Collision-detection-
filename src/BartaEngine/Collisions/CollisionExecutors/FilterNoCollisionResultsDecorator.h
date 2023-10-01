#pragma once
#include "../../pch.h"
#include "CollisionTestExecutorDecorator.h"

namespace Barta {

	class FilterNoCollisionResultsDecorator:public CollisionTestExecutorDecorator {
		public:

		FilterNoCollisionResultsDecorator(std::unique_ptr<CollisionTestExecutorInterface> decoratedObject) noexcept;

		virtual ResultsList executeTests(const CollisionAwareInterface::CollidableList& collidableList) override;
	};

}