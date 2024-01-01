#include "GunMoveSubscriber.h"

constexpr const float GunMoveSubscriber::ROTATION_SPEED = 120.f; 

constexpr const float GunMoveSubscriber::STATIONARY = 0.f; 
constexpr const float GunMoveSubscriber::ROTATING_COUNTER_CLOCKWISE = -GunMoveSubscriber::ROTATION_SPEED; 
constexpr const float GunMoveSubscriber::ROTATING_CLOCKWISE = GunMoveSubscriber::ROTATION_SPEED; 

GunMoveSubscriber::GunMoveSubscriber(
    bool* deleteWatch,
    Gun* gun
) noexcept
    : Barta::DeletableObject(deleteWatch),
    gun(gun)
{}

bool GunMoveSubscriber::handle(Barta::KeyPressedEvent &event) {
    if (event.key == Barta::BartaKeyMap::RIGHT) {
        this->gun->setRotationState(
            Gun::RotationState::CLOCKWISE,
            GunMoveSubscriber::ROTATING_CLOCKWISE
        );
    } else if (event.key == Barta::BartaKeyMap::LEFT) {
        this->gun->setRotationState(
            Gun::RotationState::COUNTER_CLOCKWISE,
            GunMoveSubscriber::ROTATING_COUNTER_CLOCKWISE
        );
    }
    
    return false;
}

bool GunMoveSubscriber::handle(Barta::KeyReleasedEvent &event) {
    if (
            event.key != Barta::BartaKeyMap::RIGHT
        &&
            event.key != Barta::BartaKeyMap::LEFT
    ) {
        return false;
    }

    this->gun->setRotationState(
        Gun::RotationState::STATIONARY,
        GunMoveSubscriber::STATIONARY
    );
    
    return false;
}

bool GunMoveSubscriber::isValid() const noexcept {
    return !this->isToBeDeleted();
}
