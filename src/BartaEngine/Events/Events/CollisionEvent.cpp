#include "pch.h"
#include "CollisionEvent.h"

bool Barta::CollisionEvent::compareObjects(CollisionAwareInterface* first, CollisionAwareInterface* second) const noexcept {
	return (first == std::get<1>(this->collisionResuslt) && second == std::get<2>(this->collisionResuslt)
			|| first == std::get<2>(this->collisionResuslt) && second == std::get<1>(this->collisionResuslt));
}