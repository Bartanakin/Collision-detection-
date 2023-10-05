#pragma once
#include<Events/Events/CollisionEvent.h>
#include<Events/BartaEventLoggerInterface.h>
#include "../../Ball.h"

class ChangeBallColorOnCollisionSubscriber: public Barta::CollisionEventSubscriberInterface {
	public:

	ChangeBallColorOnCollisionSubscriber(Ball& ball1, Ball& ball2) noexcept;
	virtual ~ChangeBallColorOnCollisionSubscriber() noexcept = default;

	bool handle(Barta::CollisionEvent& event) override;

	bool isValid() const noexcept override;

	private:

	Ball& ball1;
	Ball& ball2;
};