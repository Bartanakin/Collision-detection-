#pragma once
#include "../../pch.h"
#include "../../Geometrics/Vector2f.h"

namespace Barta {

	struct CollisionTestResult {
		const bool collisionDetected;
		const float timePassed;
		const bool staticCollision;
		const Vector2f normVector;
	
		CollisionTestResult(
			bool collisionDetected,
			float timePassed,
			bool staticCollision,
			Vector2f normVector
		) noexcept
			: collisionDetected(collisionDetected),
			timePassed(timePassed),
			staticCollision(staticCollision),
			normVector(normVector)
		{}
	};

}