#pragma once
#include "../Events/CollisionEvent.h"
#include "../Events/VelocityChangeEvent.h"

namespace Barta {

	class CollisionResponseSubscriber : public CollisionEventSubscriberInterface {
		public:
		constexpr static const float COEFFICIENT_OF_ELISTICITY = 1.f;

		CollisionResponseSubscriber(BartaEventLoggerInterface& eventLogger);
		~CollisionResponseSubscriber() = default;

		bool handle(const CollisionEvent& event) override;

		bool isValid() const noexcept override;

		private:

		BartaEventLoggerInterface& eventLogger;

		void calculateNewVelocity(
			float j,
			CollisionAwareInterface const* dynamicsObject,
			Vector2f normVector
		) const noexcept;

	};

}