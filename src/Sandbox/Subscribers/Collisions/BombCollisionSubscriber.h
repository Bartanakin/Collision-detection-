#pragma once
#include "BombWallSubscriber.h"
#include "DeletableObject.h"
#include <Events/BartaEventLoggerInterface.h>

class BombCollisionSubscriber:
    public Subscribers::BombWall,
    public Barta::DeletableObject {
	public:

	BombCollisionSubscriber(
        bool* deleteWatch
    ) noexcept;
    BombCollisionSubscriber(const BombCollisionSubscriber&) = delete;
    BombCollisionSubscriber& operator=(const BombCollisionSubscriber&) = delete;
    
	bool handle(Events::BombWall& event) override;

	bool isValid() const noexcept override;

	private:
};