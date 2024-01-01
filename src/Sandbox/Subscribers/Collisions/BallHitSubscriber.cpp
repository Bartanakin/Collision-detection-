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
    bool* deleteWatch,
    PostDynamicEventLogger& postDynamicEventLogger,
    BallList& ballList,
    StageChangeEvent::StageID& currentStageID
) noexcept
    : Barta::DeletableObject(deleteWatch),
      postDynamicEventLogger(postDynamicEventLogger),
      ballList(ballList),
      currentStageID(currentStageID)
{}

bool Subscribers::BallHit::handle(Events::BallBomb &event) {
    if (event.getTestResult().object1->isToBeDeleted() || event.getTestResult().object2->isToBeDeleted()) {
        return false;
    }

    event.getTestResult().object1->markToBeDeleted();
    event.getTestResult().object2->markToBeDeleted();
    auto ballSize = event.getTestResult().object1->getSize();
    if (ballSize == Ball::BallSize::VERY_SMALL) {
        for (const auto& ball : this->ballList) {
            if (!ball->isToBeDeleted()) {
                return true;
            }
        }

        auto stage = this->currentStageID;
        ++stage;
        if (stage == StageChangeEvent::StageID::UNDEFINED) {
            this->postDynamicEventLogger.logEvent(StageChangeEvent(stage));
            this->postDynamicEventLogger.logEvent(FlashMessageEvent(
                "Congratulations! You've completed all stages!",
                4s
            ));

            return true;
        }

        this->postDynamicEventLogger.logEvent(StageChangeEvent(stage));
        this->postDynamicEventLogger.logEvent(FlashMessageEvent(
            "Stage " + std::to_string(static_cast<int>(stage)),
            3s
        ));

        return true;
    }
    
    const auto old_radius = Ball::ballSize(ballSize);
    --ballSize;
    const auto& dynamics = event.getTestResult().object2->getDynamicsDTO();
    const auto move_pos = Barta::Vector2f(Ball::ballSize(ballSize), 0.f);
    const auto pos = event.getTestResult().object1->getTransformable().getPosition()
                     + Barta::Vector2f(old_radius, old_radius) - move_pos;
    const auto p_y = dynamics.velocity.y * dynamics.mass;
    const auto v_x = Ball::horizontalSpeed;
    const auto n = event.getTestResult().collisionTestResult.normVector.normalised(); 
    const auto sin = d ^ n;
    const auto cos = d * n;

    Barta::Vector2f v1 = { sgn(cos) * v_x, sgn(sin)* sgn(p_y) * cos * cos * p_y };
    Barta::Vector2f v2 = { - sgn(sin) * v_x, sgn(cos)* sgn(p_y) * sin * sin * p_y };

    auto b1 = new Ball(pos + sgn(cos) * move_pos, false, ballSize);
    b1->setVelocity(v1);
    this->postDynamicEventLogger.logEvent(BallCreateEvent(std::unique_ptr<Ball>(b1)));
    
    auto b2 = new Ball(pos - sgn(cos) * move_pos, false, ballSize);
    b2->setVelocity(v2);
    this->postDynamicEventLogger.logEvent(BallCreateEvent(std::unique_ptr<Ball>(b2)));

    return true;
}

bool Subscribers::BallHit::isValid() const noexcept {
    return !this->isToBeDeleted();
}
