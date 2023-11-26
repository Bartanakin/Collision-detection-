#pragma once
#include "../../Geometrics/Vector2f.h"
#include "../TemplateEventSubscriber.h"
#include "../../Collisions/CollisionExecutors/CollisionTestExecutorInterface.h"
#include "../../Tests/Utilities/TestUtilities.h"

#define DEBUG_COLLISION_EVENT 0

namespace Barta {

	class DynamicsChangeEvent {
		public:
		DynamicsChangeEvent(DynamicsAwareInterface* dynamicsAware, DynamicsDTO newDynamics) noexcept:
			dynamicsAware(dynamicsAware), dynamicsDiff(newDynamics) {
		}

		DynamicsAwareInterface* dynamicsAware;
		DynamicsDTO dynamicsDiff;
	};

	template<>
	class EventSubscriber<DynamicsChangeEvent> {
		public:
        virtual ~EventSubscriber() noexcept = default;

		virtual bool handle(DynamicsChangeEvent& event) = 0;

		virtual bool isValid() const noexcept = 0;
	};

	typedef EventSubscriber<DynamicsChangeEvent> DynamicsChangeSubscriberInterface;
}

