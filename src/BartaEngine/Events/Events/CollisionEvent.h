#pragma once
#include "../../Geometrics/Vector2f.h"
#include "../TemplateEventSubscriber.h"
#include "../../Collisions/CollisionExecutors/CollisionTestExecutorInterface.h"
#include "../../Tests/Utilities/TestUtilities.h"

#define DEBUG_COLLISION_EVENT 0

namespace Barta {

	class CollisionEvent 
		#if DEBUG_COLLISION_EVENT 
		: public bits_of_q::CopyCounter
		#endif
	{
		using ExtendedCollisionResult = std::tuple<
			CollisionTestResult,
			CollisionAwareInterface*,
			CollisionAwareInterface*
		>;
		public:
		CollisionEvent(const ExtendedCollisionResult collisionResuslt, float delta_t) noexcept:
			collisionResuslt(std::move(collisionResuslt)), delta_t(delta_t) {}
        virtual ~CollisionEvent() noexcept = default;

		bool compareObjects(CollisionAwareInterface* first, CollisionAwareInterface* second) const noexcept;

		inline const ExtendedCollisionResult getTestResult() const noexcept {
			return this->collisionResuslt;
		}

		inline float getDelta_t() const noexcept {
			return this->delta_t;
		}

		private:
		const ExtendedCollisionResult collisionResuslt;
		const float delta_t;
	};

	template<>
	class EventSubscriber<CollisionEvent> {
		public:
        virtual ~EventSubscriber() noexcept = default;

		virtual bool handle(CollisionEvent& event) = 0;

		virtual bool isValid() const noexcept = 0;
	};

	typedef EventSubscriber<CollisionEvent> CollisionEventSubscriberInterface;
}

