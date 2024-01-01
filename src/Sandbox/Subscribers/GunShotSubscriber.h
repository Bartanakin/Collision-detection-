#pragma once
#include <Events/Events/KeyPressedEvent.h>
#include <Events/Events/KeyReleasedEvent.h>
#include "../Player.h"
#include "../ListsDefinitions.h"
#include <ObjectManagerInterface.h>

class GunShotSubscriber:
    public Barta::KeyPressedSubscriberInterface,
    public Barta::DeletableObject {
	public:

    static const float INITIAL_SPEED;

	GunShotSubscriber(
        bool* deleteWatch,
        Player* player,
        BombList& bombList,
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
    Barta::ObjectManagerInterface& objectManager;
};