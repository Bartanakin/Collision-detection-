#include "pch.h"
#include "CollisionEvent.h"

bool Barta::CollisionEvent::compareObjects(CollisionAwareInterface* first, CollisionAwareInterface* second) const noexcept {
	return ((first == this->collisionResuslt.object1 && second == this->collisionResuslt.object2)
			|| (first == this->collisionResuslt.object2 && second == this->collisionResuslt.object1));
}

bool Barta::CollisionEvent::isOneOf(
    CollisionAwareInterface *needle
) const noexcept {
    return this->collisionResuslt.object1 == needle || collisionResuslt.object2 == needle;
}
