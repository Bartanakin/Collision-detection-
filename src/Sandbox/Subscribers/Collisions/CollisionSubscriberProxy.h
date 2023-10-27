#pragma once
#include<Events/Events/CollisionEvent.h>
#include "../../Player.h"
#include "../../ListsDefinitions.h"

class CollisionSubscriberProxy:
    public Barta::CollisionEventSubscriberInterface {
	public:

	CollisionSubscriberProxy(
        Player* player,
        BombList& bombList,
        std::unique_ptr<Barta::CollisionEventSubscriberInterface> collisionSubscriber,
        std::unique_ptr<Barta::CollisionEventSubscriberInterface> bombCollisionSubscriber
    ) noexcept;
    CollisionSubscriberProxy(const CollisionSubscriberProxy&) = delete;
    CollisionSubscriberProxy& operator=(const CollisionSubscriberProxy&) = delete;

	bool handle(Barta::CollisionEvent& event) override;

	bool isValid() const noexcept override;

	private:

    Player* player;
    BombList& bombList;
    std::unique_ptr<Barta::CollisionEventSubscriberInterface> collisionSubscriber;
    std::unique_ptr<Barta::CollisionEventSubscriberInterface> bombCollisionSubscriber;
};