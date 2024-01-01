#pragma once


#include "PlayerWallSubscriber.h"
namespace Subscribers {
class PlayerWallCollisionSubscriber :
    public Subscribers::PlayerWall,
    public Barta::DeletableObject {
public:
    PlayerWallCollisionSubscriber(
        bool* deleteWatch
    ) noexcept;
    PlayerWallCollisionSubscriber(const PlayerWallCollisionSubscriber&) = delete;
    PlayerWallCollisionSubscriber& operator=(const PlayerWallCollisionSubscriber&) = delete;

    bool isValid() const noexcept override;
    bool handle(Events::PlayerWall &event) override;
};

};
