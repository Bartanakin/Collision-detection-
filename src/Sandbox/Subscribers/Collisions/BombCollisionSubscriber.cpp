#include "BombCollisionSubscriber.h"

BombCollisionSubscriber::BombCollisionSubscriber(
    BombList& bombList,
    std::vector<GiantBlock*> walls,
    BallList& ballList
) noexcept :
    bombList(bombList),
    walls(std::move(walls)),
    ballList(ballList)
{}

bool BombCollisionSubscriber::handle(Barta::CollisionEvent &event) {
    Bomb* bomb = event.matchFromList<Bomb, BombList>(this->bombList);
    if (bomb == nullptr)
        throw "No bomb found";

    GiantBlock* wall = event.matchFromList<GiantBlock, std::vector<GiantBlock*>>(this->walls);
    if (wall != nullptr)
        return this->handleWall(event.getTestResult(), wall, bomb);

    Ball* ball = event.matchFromList<Ball, BallList>(this->ballList);
    if (ball != nullptr)
        return this->handleBall(event.getTestResult(), ball, bomb);
    
    throw "Neither ball nor wall found!";
}

bool BombCollisionSubscriber::isValid() const noexcept {
    return true;
}

bool BombCollisionSubscriber::handleWall(
    const Barta::ExtendedCollisionResult &collisionResult,
    GiantBlock *wall,
    Bomb *bomb
) const {
                    std::cout << "XD" << std::endl;
    bomb->markToBeDeleted();
    this->bombList.reduce();

    return false;
}

bool BombCollisionSubscriber::handleBall(
    const Barta::ExtendedCollisionResult &collisionResult,
    Ball *ball,
    Bomb *bomb
) const {
    return false;
}
