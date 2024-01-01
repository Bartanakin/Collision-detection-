#pragma once

#include "CustomEvents/PostDynamicEventLogger.h"
#include "PlayerBallSubscriber.h"
namespace Subscribers {

class PlayerHitSubscriber :
    public PlayerBall,
    public Barta::DeletableObject {
public:
    PlayerHitSubscriber(
        bool* deleteWatch,
        PostDynamicEventLogger& postDynamicEventLogger
    ) noexcept;
    PlayerHitSubscriber(const PlayerHitSubscriber&) = delete;
    PlayerHitSubscriber& operator=(const PlayerHitSubscriber&) = delete;

    bool isValid() const noexcept override;
    bool handle(Events::PlayerBall &event) override;

private:
    PostDynamicEventLogger& postDynamicEventLogger;
};

} // namespace Subscribers
