#pragma once
#include "../../pch.h"
#include "CollisionTestExecutorInterface.h"

namespace Barta {

	class CollisionTestExecutorDecorator:public CollisionTestExecutorInterface {
		public:

		CollisionTestExecutorDecorator(std::unique_ptr<CollisionTestExecutorInterface> decoratedObject) noexcept;
		virtual ~CollisionTestExecutorDecorator() = default;

		inline virtual ResultsList executeTests(const CollisionAwareInterface::CollidableList& collidableList) override;

		protected:

		std::unique_ptr<CollisionTestExecutorInterface> decoratedObject;
	};

}

