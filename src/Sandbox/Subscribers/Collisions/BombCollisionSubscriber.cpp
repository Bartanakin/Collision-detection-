#include "BombCollisionSubscriber.h"

BombCollisionSubscriber::BombCollisionSubscriber() noexcept :
    Subscribers::BombWall()
{}

bool BombCollisionSubscriber::handle(Events::BombWall &event) {
    event.getTestResult().object1->markToBeDeleted();

    return false;
}

bool BombCollisionSubscriber::isValid() const noexcept {
    return true;
}
