#pragma once
#include<Events/Events/CollisionEvent.h>
#include<Events/BartaEventLoggerInterface.h>
#include "BombWallSubscriber.h"

class BombCollisionSubscriber:
    public Subscribers::BombWall {
	public:

	BombCollisionSubscriber() noexcept;
    BombCollisionSubscriber(const BombCollisionSubscriber&) = delete;
    BombCollisionSubscriber& operator=(const BombCollisionSubscriber&) = delete;
    
	bool handle(Events::BombWall& event) override;

	bool isValid() const noexcept override;

	private:
};