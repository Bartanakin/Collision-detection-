//
// Created by barta on 29/12/2023.
//

#include "PlayerWallCollisionSubscriber.h"
#include "../PlayerMoveSubscriber.h"
Subscribers::PlayerWallCollisionSubscriber::PlayerWallCollisionSubscriber(
    bool *deleteWatch
) noexcept
    : DeletableObject(deleteWatch)
{}

bool Subscribers::PlayerWallCollisionSubscriber::isValid() const noexcept {
    return !this->isToBeDeleted();
}

bool Subscribers::PlayerWallCollisionSubscriber::handle(Events::PlayerWall &event) {
    auto player = event.getTestResult().object1;
    auto normalVectorX = event.getTestResult().collisionTestResult.normVector.x;

    if (player->getScenePosition() == Player::Position::LOOSE && normalVectorX > 0.f) {
        player->setScenePosition(Player::Position::LEFT_WALL);
        player->setVelocity(PlayerMoveSubscriber::STATIONARY);
    }

    if (player->getScenePosition() == Player::Position::LOOSE && normalVectorX < 0.f) {
        player->setScenePosition(Player::Position::RIGHT_WALL);
        player->setVelocity(PlayerMoveSubscriber::STATIONARY);
    }

    return false;
}
