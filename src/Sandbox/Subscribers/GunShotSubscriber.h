#pragma once
#include <Events/Events/KeyPressedEvent.h>
#include <Events/Events/KeyReleasedEvent.h>
#include <Events/Events/CollisionEvent.h>
#include "../Player.h"
#include "../ListsDefinitions.h"
#include <ObjectManagerInterface.h>

class GunShotSubscriber:
    public Barta::KeyPressedSubscriberInterface {
	public:

    static const float INITIAL_SPEED;

	GunShotSubscriber(
        Player* player,
        BombList& bombList,
        const Barta::Vector2f gravity,
        Barta::ObjectManagerInterface& objectManager
    ) noexcept;
	GunShotSubscriber(const GunShotSubscriber&) = delete;
	GunShotSubscriber& operator=(const GunShotSubscriber&) = delete;
	virtual ~GunShotSubscriber() noexcept = default;

	bool handle(Barta::KeyPressedEvent& event) override;

	bool isValid() const noexcept override;

	private:

    Player* player;
    BombList& bombList;
    const Barta::Vector2f gravity;
    Barta::ObjectManagerInterface& objectManager;
};