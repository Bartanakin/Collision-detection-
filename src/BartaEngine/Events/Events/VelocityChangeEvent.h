#pragma once
#include "../../Geometrics/Vector2f.h"
#include "../TemplateEventSubscriber.h"
#include "../../Collisions/CollisionExecutors/CollisionTestExecutorInterface.h"
#include "../../Tests/Utilities/TestUtilities.h"

#define DEBUG_COLLISION_EVENT 0

namespace Barta {

	class DynamicsChangeEvent
		#if DEBUG_COLLISION_EVENT 
		: public bits_of_q::CopyCounter
		#endif
	{
		public:
		DynamicsChangeEvent(DynamicsAwareInterface const* dynamicsAware, DynamicsDTO newDynamics) noexcept:
			dynamicsAware(dynamicsAware), newDynamics(newDynamics) {
		}

		DynamicsAwareInterface const* dynamicsAware;
		DynamicsDTO newDynamics;
	};

	template<>
	class EventSubscriber<const DynamicsChangeEvent> {
		public:

		virtual bool handle(const DynamicsChangeEvent& event) = 0;

		virtual bool isValid() const noexcept = 0;
	};

	typedef EventSubscriber<const DynamicsChangeEvent> DynamicsChangeSubscriberInterface;
}

