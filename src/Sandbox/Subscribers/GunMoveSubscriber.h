#pragma once
#include "../Gun.h"
#include "DeletableObject.h"
#include <Events/Events/KeyPressedEvent.h>
#include <Events/Events/KeyReleasedEvent.h>

class GunMoveSubscriber:
    public Barta::KeyPressedSubscriberInterface,
    public Barta::KeyReleasedSubscriberInterface,
    public Barta::DeletableObject {
	public:

    static const float ROTATION_SPEED;

    static const float STATIONARY;
    static const float ROTATING_COUNTER_CLOCKWISE;
    static const float ROTATING_CLOCKWISE;

	GunMoveSubscriber(
        bool* deleteWatch,
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