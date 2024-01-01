#pragma once
#include <Events/Events/KeyPressedEvent.h>
#include <Events/Events/KeyReleasedEvent.h>
#include "../Player.h"
#include "../Wall.h"

class PlayerMoveSubscriber:
    public Barta::KeyPressedSubscriberInterface,
    public Barta::KeyReleasedSubscriberInterface,
    public Barta::DeletableObject {
	public:

    static const float MOVEMENT_SPEED;

    static const Barta::Vector2f STATIONARY;
    static const Barta::Vector2f MOVING_LEFT;
    static const Barta::Vector2f MOVING_RIGHT;

	PlayerMoveSubscriber(
        bool* deleteWatch,
        Player* player
    ) noexcept;
	PlayerMoveSubscriber(const PlayerMoveSubscriber&) = delete;
	PlayerMoveSubscriber& operator=(const PlayerMoveSubscriber&) = delete;
	virtual ~PlayerMoveSubscriber() noexcept = default;

	bool handle(Barta::KeyPressedEvent& event) override;

	bool handle(Barta::KeyReleasedEvent& event) override;

	bool isValid() const noexcept override;

	private:

    Player* player;
};