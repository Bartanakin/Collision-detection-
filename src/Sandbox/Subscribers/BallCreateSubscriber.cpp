#include "BallCreateSubscriber.h"

BallCreateSubscriber::BallCreateSubscriber(
    Barta::ObjectManagerInterface &objectManager,
    BallList &ballList
) noexcept :
    objectManager(objectManager),
    ballList(ballList)
{}

bool BallCreateSubscriber::handle(BallCreateEvent &event) {
    auto ball = event.ball.release();
    if (ball != nullptr) {
        this->ballList.push_back(ball);
        this->objectManager.addDynamicsObject(ball);
        this->objectManager.addNewObject(ball);    
    }

    return true;
}

bool BallCreateSubscriber::isValid() const noexcept {
    return true;
}
