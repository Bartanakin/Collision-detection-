#include "BombCollisionSubscriber.h"

BombCollisionSubscriber::BombCollisionSubscriber(
    bool* deleteWatch
) noexcept
    : Subscribers::BombWall(),
      Barta::DeletableObject(deleteWatch)
{}

bool BombCollisionSubscriber::handle(Events::BombWall &event) {
    event.getTestResult().object1->markToBeDeleted();

    return false;
}

bool BombCollisionSubscriber::isValid() const noexcept {
    return !this->isToBeDeleted();
}
