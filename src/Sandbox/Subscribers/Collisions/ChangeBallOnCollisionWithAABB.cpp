#include "ChangeBallOnCollisionWithAABB.h"

ChangeBallOnCollisionWithAABB::ChangeBallOnCollisionWithAABB(Ball& ball, Block& block) noexcept:
	ball(ball), block(block) {
}

bool ChangeBallOnCollisionWithAABB::handle(Barta::CollisionEvent& event) {
	if (!event.compareObjects(static_cast<Barta::CollisionAwareInterface*>(&this->ball), static_cast<Barta::CollisionAwareInterface*>(&this->block))) {
		return false;
	}

	ball.setBallCollor(Barta::Resource::GREEN_BALL);

	return true;
}

bool ChangeBallOnCollisionWithAABB::isValid() const noexcept {
	return true;
}
