#pragma once
#include "../../pch.h"
#include "CollisionTestResult.h"
#include "../CollisionAwareInterface.h"

namespace Barta {

	struct ExtendedCollisionResult {
        CollisionTestResult collisionTestResult;
        CollisionAwareInterface* object1;
        CollisionAwareInterface* object2;
	
        ExtendedCollisionResult() noexcept :
            collisionTestResult({}),
            object1(nullptr),
            object2(nullptr)
        {}
		
        // shallow copy
        ExtendedCollisionResult(const ExtendedCollisionResult& second) noexcept :
            collisionTestResult(second.collisionTestResult),
            object1(second.object1),
            object2(second.object2)
		{}
		
        ExtendedCollisionResult(
            CollisionTestResult collisionTestResult,
            CollisionAwareInterface* object1,
            CollisionAwareInterface* object2
		) noexcept :
            collisionTestResult(collisionTestResult),
            object1(object1),
            object2(object2)
		{}

        ExtendedCollisionResult& operator=(const ExtendedCollisionResult& second) noexcept {
            this->collisionTestResult = second.collisionTestResult;
            this->object1 = second.object1;
            this->object2 = second.object2;

            return *this;
        }

        bool operator==(const ExtendedCollisionResult& second) const noexcept {
            return this->collisionTestResult == second.collisionTestResult
                && (
                    (this->object1 == second.object1 && this->object2 == second.object2)
                    ||
                    (this->object2 == second.object1 && this->object1 == second.object2)
                );
        }
	};

}