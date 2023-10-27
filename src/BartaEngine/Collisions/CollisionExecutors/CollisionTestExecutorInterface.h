#pragma once
#include "../../pch.h"
#include "../CollisionAwareInterface.h"
#include "../CollcionTestResult/ExtendedCollisionResult.h"

namespace Barta {

	class CollisionTestExecutorInterface {
		public:
		CollisionTestExecutorInterface() = default;
		virtual ~CollisionTestExecutorInterface() = default;

		typedef std::list<ExtendedCollisionResult> ResultsList;

		virtual ResultsList executeTests(const CollisionAwareInterface::CollidableList& collidableList) = 0;
	};

}