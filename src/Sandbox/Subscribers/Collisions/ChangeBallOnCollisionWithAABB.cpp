#include "ChangeBallOnCollisionWithAABB.h"

ChangeBallOnCollisionWithAABB::ChangeBallOnCollisionWithAABB(Ball& ball, Block& block) noexcept:
	ball(ball), block(block) {
}

bool ChangeBallOnCollisionWithAABB::handle(const Barta::CollisionEvent& event) {
	if (!event.compareObjects((Barta::CollisionAwareInterface*) &this->ball, (Barta::CollisionAwareInterface*) &this->block)) {
		return false;
	}

	ball.setBallCollor(Barta::Resource::GREEN_BALL);

	return true;
}

bool ChangeBallOnCollisionWithAABB::isValid() const noexcept {
	return true;
}
