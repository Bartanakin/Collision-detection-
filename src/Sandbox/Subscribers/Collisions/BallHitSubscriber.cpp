#include "BallHitSubscriber.h"

const Barta::Vector2f Subscribers::BallHit::d = { std::sqrt(2.f) / 2.f, std::sqrt(2.f) / 2.f };

namespace {
    float sgn(float x) {
        if (x > 0) {
            return 1.;
        } else if (x < 0) {
            return -1.;
        } else {
            return 0.;
        }
    }
}

Subscribers::BallHit::BallHit(
    PostDynamicEventLogger& postDynamicEventLogger,
    const Barta::Vector2f gravity
) noexcept :
    postDynamicEventLogger(postDynamicEventLogger),
    gravity(gravity)
{}

bool Subscribers::BallHit::handle(Events::BallBomb &event) {
    if (event.getTestResult().object1->isToBeDeleted() || event.getTestResult().object2->isToBeDeleted()) {
        return false;
    }

    event.getTestResult().object1->markToBeDeleted();
    event.getTestResult().object2->markToBeDeleted();
    auto ballSize = event.getTestResult().object1->getSize();
    if (ballSize == Ball::BallSize::VERY_SMALL) {
        return true;
    }
    
    const auto old_radius = Ball::ballSize(ballSize);
    --ballSize;
    const auto& dynamics = event.getTestResult().object2->getDynamicsDTO(); 
    const auto pos = event.getTestResult().object1->getTransformable().getPosition() + Barta::Vector2f(old_radius, old_radius);
    const auto move_pos = Barta::Vector2f(Ball::ballSize(ballSize), 0.f);
    const auto p_y = dynamics.velocity.y * dynamics.mass;
    const auto v_x = Ball::horizontalSpeed;
    const auto n = event.getTestResult().collisionTestResult.normVector.normalised(); 
    const auto sin = d ^ n;
    const auto cos = d * n;

    Barta::Vector2f v1 = { sgn(cos) * v_x, sgn(sin)* sgn(p_y) * cos * cos * p_y };
    Barta::Vector2f v2 = { - sgn(sin) * v_x, sgn(cos)* sgn(p_y) * sin * sin * p_y };

    auto b1 = new Ball(pos + sgn(cos) * move_pos, false, ballSize, this->gravity);
    b1->setVelocity(v1);
    this->postDynamicEventLogger.logEvent(BallCreateEvent(std::move(std::unique_ptr<Ball>(b1))));
    
    auto b2 = new Ball(pos - sgn(cos) * move_pos, false, ballSize, this->gravity);
    b2->setVelocity(v2);
    this->postDynamicEventLogger.logEvent(BallCreateEvent(std::move(std::unique_ptr<Ball>(b2))));

    return true;
}

bool Subscribers::BallHit::isValid() const noexcept {
    return true;
}
