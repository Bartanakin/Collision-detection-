#pragma once
#include "../../pch.h"
#include "../CollisionAwareInterface.h"
#include "../../Events/BartaEventLoggerInterface.h"

namespace Barta {

	class CollisionTestExecutorInterface {
		public:
		CollisionTestExecutorInterface() = default;
		virtual ~CollisionTestExecutorInterface() = default;

		using ExtendedCollisionResult = std::tuple<
			CollisionTestResult,
			CollisionAwareInterface*,
			CollisionAwareInterface*
		>;
		typedef std::list<ExtendedCollisionResult> ResultsList;

		virtual ResultsList executeTests(const CollisionAwareInterface::CollidableList& collidableList) = 0;
	};

}