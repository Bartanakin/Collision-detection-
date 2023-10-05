#include "ChangeBallColorOnCollisionSubscriber.h"

ChangeBallColorOnCollisionSubscriber::ChangeBallColorOnCollisionSubscriber(Ball& ball1, Ball& ball2) noexcept :
	ball1(ball1), ball2(ball2)
{
}

bool ChangeBallColorOnCollisionSubscriber::handle(Barta::CollisionEvent& event) {
	if (!event.compareObjects(static_cast<Barta::CollisionAwareInterface*>(&this->ball1), static_cast<Barta::CollisionAwareInterface*>(&this->ball2))) {
		return false;
	}

	ball1.setBallCollor(Barta::Resource::GREEN_BALL);
	ball2.setBallCollor(Barta::Resource::GREEN_BALL);

	return true;
}

bool ChangeBallColorOnCollisionSubscriber::isValid() const noexcept {
	return true;
}
