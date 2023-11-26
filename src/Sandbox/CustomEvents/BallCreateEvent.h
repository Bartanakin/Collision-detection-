#pragma once
#include <Events/TemplateEventSubscriber.h>
#include <BartaObjectManager.h>
#include "../Ball.h"

class BallCreateEvent {
    public:
    BallCreateEvent(
        std::unique_ptr<Ball> ball
    ) noexcept: 
        ball(std::move(ball))
    {}
    BallCreateEvent(const BallCreateEvent&) = delete;
    BallCreateEvent(BallCreateEvent&&) noexcept = default;
    BallCreateEvent& operator=(const BallCreateEvent&) = delete;
    ~BallCreateEvent() noexcept = default;

    std::unique_ptr<Ball> ball;
};

template<>
class Barta::EventSubscriber<BallCreateEvent> {
    public:
    virtual ~EventSubscriber() noexcept = default;

    virtual bool handle(BallCreateEvent& event) = 0;

    virtual bool isValid() const noexcept = 0;
};

typedef Barta::EventSubscriber<BallCreateEvent> BallCreateSubscriberInterface;

