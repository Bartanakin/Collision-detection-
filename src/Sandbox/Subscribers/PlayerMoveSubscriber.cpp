#include "PlayerMoveSubscriber.h"

constexpr const float PlayerMoveSubscriber::MOVEMENT_SPEED = 120.f; 

constexpr const Barta::Vector2f PlayerMoveSubscriber::STATIONARY = {}; 
constexpr const Barta::Vector2f PlayerMoveSubscriber::MOVING_LEFT = {-PlayerMoveSubscriber::MOVEMENT_SPEED, 0.f}; 
constexpr const Barta::Vector2f PlayerMoveSubscriber::MOVING_RIGHT = {PlayerMoveSubscriber::MOVEMENT_SPEED, 0.f}; 

PlayerMoveSubscriber::PlayerMoveSubscriber(
    bool* deleteWatch,
    Player *player
) noexcept
    : Barta::DeletableObject(deleteWatch),
    player(player)
{}

bool PlayerMoveSubscriber::handle(Barta::KeyPressedEvent &event) {
    if (event.key == Barta::BartaKeyMap::A && player->getScenePosition() != Player::Position::LEFT_WALL) {
        player->setVelocity(PlayerMoveSubscriber::MOVING_LEFT);
        player->setScenePosition(Player::Position::LOOSE);
    } else if (event.key == Barta::BartaKeyMap::D && player->getScenePosition() != Player::Position::RIGHT_WALL) {
        player->setVelocity(PlayerMoveSubscriber::MOVING_RIGHT);
        player->setScenePosition(Player::Position::LOOSE);
    }

    return false;
}

bool PlayerMoveSubscriber::handle(Barta::KeyReleasedEvent &event) {
    if (event.key != Barta::BartaKeyMap::A && event.key != Barta::BartaKeyMap::D) {
        return false;
    }

    player->setVelocity(PlayerMoveSubscriber::STATIONARY);

    return false;
}

bool PlayerMoveSubscriber::isValid() const noexcept {
    return !this->isToBeDeleted();
}
