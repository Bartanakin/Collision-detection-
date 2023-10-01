#pragma once
#include<Events/Events/CollisionEvent.h>
#include<Events/BartaEventLoggerInterface.h>
#include "../../Ball.h"
#include "../../Block.h"

class ChangeBallOnCollisionWithAABB: public Barta::CollisionEventSubscriberInterface {
	public:

	ChangeBallOnCollisionWithAABB(Ball& ball, Block& block) noexcept;
	virtual ~ChangeBallOnCollisionWithAABB() noexcept = default;

	bool handle(const Barta::CollisionEvent& event) override;

	bool isValid() const noexcept override;

	private:

	Ball& ball;
	Block& block;
};