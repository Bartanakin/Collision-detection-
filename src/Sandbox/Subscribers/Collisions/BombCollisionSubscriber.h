#pragma once
#include<Events/Events/CollisionEvent.h>
#include<Events/BartaEventLoggerInterface.h>
#include "../../Objects/GiantBlock.h"
#include "../../ListsDefinitions.h"

class BombCollisionSubscriber:
    public Barta::CollisionEventSubscriberInterface {
	public:

	BombCollisionSubscriber(
        BombList& bombList,
        std::vector<GiantBlock*> walls,
        BallList& ballList
    ) noexcept;
    BombCollisionSubscriber(const BombCollisionSubscriber&) = delete;
    BombCollisionSubscriber& operator=(const BombCollisionSubscriber&) = delete;

	bool handle(Barta::CollisionEvent& event) override;

	bool isValid() const noexcept override;

    bool handleWall(const Barta::ExtendedCollisionResult& collisionResult, GiantBlock* wall, Bomb* bomb) const;
    bool handleBall(const Barta::ExtendedCollisionResult& collisionResult, Ball* ball, Bomb* bomb) const;

	private:

    BombList& bombList;
    std::vector<GiantBlock*> walls;
    BallList& ballList;
};