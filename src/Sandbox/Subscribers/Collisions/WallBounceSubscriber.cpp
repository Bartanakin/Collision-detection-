#include "WallBounceSubscriber.h"
#include <Events/Events/VelocityChangeEvent.h>


Subscribers::WallBounce::WallBounce(
    Barta::BartaEventLoggerInterface &eventLogger
) noexcept :
    eventLogger(eventLogger),
    innerSubscriber(Barta::StaticCollisionResponseSubscriberType<Ball, Wall>(eventLogger))
{}

bool Subscribers::WallBounce::handle(Events::BallWall &event) {
    if (event.getTestResult().collisionTestResult.normVector != Barta::Vector2f(0.f, -1.f)) {
        return this->innerSubscriber.handle(event);
    }

    auto ball = event.getTestResult().object1;
    const auto& dynamics = ball->getDynamicsDTO();
    this->eventLogger.logEvent(Barta::DynamicsChangeEvent(
        static_cast<Barta::DynamicsAwareInterface*>(ball),
        Barta::DynamicsDTO({0.f, -dynamics.velocity.y - ball->getRebounceVelocity()})
    ));

    return true;
}

bool Subscribers::WallBounce::isValid() const noexcept {
    return true;
}
