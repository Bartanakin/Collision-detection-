#pragma once
#include "../../pch.h"
#include "../../Geometrics/Vector2f.h"

namespace Barta {

	struct CollisionTestResult {
		const bool collisionDetected;
		const bool staticCollision;
		const float timePassed;
		const Vector2f normVector;
	
		inline CollisionTestResult(
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