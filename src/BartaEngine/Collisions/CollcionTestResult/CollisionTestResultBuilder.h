#pragma once
#include "../../pch.h"
#include "CollisionTestResult.h"

namespace Barta {

	class CollisionTestResultBuilder {
		public:
		CollisionTestResultBuilder() noexcept;

		CollisionTestResult build() const noexcept;
		void reset() noexcept;
		CollisionTestResultBuilder* setCollisionDetected(bool data) noexcept;
		CollisionTestResultBuilder* setTimePassed(float data) noexcept;
		CollisionTestResultBuilder* setStaticCollision(float data) noexcept;
		CollisionTestResultBuilder* setNormVector(Vector2f data) noexcept;

		private:
		bool collisionDetected;
		float timePassed;
		float staticCollision;
		Vector2f normVector;
	};

}