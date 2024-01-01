#pragma once
#include "../CustomEvents/BallCreateEvent.h"
#include "../ListsDefinitions.h"
#include <ObjectManagerInterface.h>

class BallCreateSubscriber:
    public BallCreateSubscriberInterface,
    public Barta::DeletableObject {
	public:
	BallCreateSubscriber(
        bool* deleteWatch,
        Barta::ObjectManagerInterface& objectManager,
        BallList& ballList
    ) noexcept;
	BallCreateSubscriber(const BallCreateSubscriber&) = delete;
	BallCreateSubscriber& operator=(const BallCreateSubscriber&) = delete;
	virtual ~BallCreateSubscriber() noexcept = default;

	bool handle(BallCreateEvent& event) override;

	bool isValid() const noexcept override;

	private:

    Barta::ObjectManagerInterface& objectManager;
    BallList& ballList;
};