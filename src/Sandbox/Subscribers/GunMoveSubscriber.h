#pragma once
#include <Events/Events/KeyPressedEvent.h>
#include <Events/Events/KeyReleasedEvent.h>
#include "../Gun.h"

class GunMoveSubscriber:
    public Barta::KeyPressedSubscriberInterface,
    public Barta::KeyReleasedSubscriberInterface {
	public:

    static const float ROTATION_SPEED;

    static const float STATIONARY;
    static const float ROTATING_COUNTER_CLOCKWISE;
    static const float ROTATING_CLOCKWISE;

	GunMoveSubscriber(
        Gun* gun
    ) noexcept;
	GunMoveSubscriber(const GunMoveSubscriber&) = delete;
	GunMoveSubscriber& operator=(const GunMoveSubscriber&) = delete;
	virtual ~GunMoveSubscriber() noexcept = default;

	bool handle(Barta::KeyPressedEvent& event) override;

	bool handle(Barta::KeyReleasedEvent& event) override;

	bool isValid() const noexcept override;

	private:

    Gun* gun;
};