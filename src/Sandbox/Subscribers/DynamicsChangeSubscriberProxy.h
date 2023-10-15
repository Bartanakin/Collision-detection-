#pragma once
#include<Events/Events/CollisionEvent.h>
#include<Events/Events/VelocityChangeEvent.h>
#include<Events/BartaEventLoggerInterface.h>
#include "../Player.h"

class DynamicsChangeSubscriberProxy:
    public Barta::DynamicsChangeSubscriberInterface {
	public:

	DynamicsChangeSubscriberProxy(
        Player* player,
        std::unique_ptr<Barta::DynamicsChangeSubscriberInterface> dynamicsChangeSubscriber
    ) noexcept;
    DynamicsChangeSubscriberProxy(const DynamicsChangeSubscriberProxy&) = delete;
    DynamicsChangeSubscriberProxy& operator=(const DynamicsChangeSubscriberProxy&) = delete;


	bool handle(Barta::DynamicsChangeEvent& event) override;

	bool isValid() const noexcept override;

	private:

    Player* player;
    std::unique_ptr<Barta::DynamicsChangeSubscriberInterface> dynamicsChangeSubscriber;
};