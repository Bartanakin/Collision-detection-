#include "CollisionSubscriberProxy.h"

CollisionSubscriberProxy::CollisionSubscriberProxy(
    Player* player,
    BombList& bombList,
    std::unique_ptr<Barta::CollisionEventSubscriberInterface> collisionSubscriber,
    std::unique_ptr<Barta::CollisionEventSubscriberInterface> bombCollisionSubscriber
) noexcept :
    player(player),
    bombList(bombList),
    collisionSubscriber(std::move(collisionSubscriber)),
    bombCollisionSubscriber(std::move(bombCollisionSubscriber))
{}

bool CollisionSubscriberProxy::handle(Barta::CollisionEvent &event) {
    if (event.isOneOf(static_cast<Barta::CollisionAwareInterface*>(this->player)))
        return false;

    if (nullptr != event.matchFromList<Bomb, BombList>(this->bombList))
        return this->bombCollisionSubscriber->handle(event);

    return this->collisionSubscriber->handle(event);
}

bool CollisionSubscriberProxy::isValid() const noexcept {
    return true;
}
