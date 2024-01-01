#include "GunShotSubscriber.h"
#define M_PI 3.14159265358979323846f

constexpr const float GunShotSubscriber::INITIAL_SPEED = 400.f; 

GunShotSubscriber::GunShotSubscriber(
    bool* deleteWatch,
    Player* player,
    BombList &bombList,
    Barta::ObjectManagerInterface& objectManager
) noexcept
    : Barta::DeletableObject(deleteWatch),
    player(player),
    bombList(bombList),
    objectManager(objectManager)
{}

bool GunShotSubscriber::handle(Barta::KeyPressedEvent &event) {
    if (event.key != Barta::BartaKeyMap::SPACEBAR) {
        return false;
    }

    if (this->player->getGun()->getLeftToReload() > 0s) {
        return false;
    }

    auto bomb = new Bomb(
        this->player->getTransformable().getPosition() + Barta::Vector2f(10.f, 10.f),
        {
            {
                INITIAL_SPEED * std::cos((this->player->getGun()->getRotation() - 90.f) * M_PI / 180.f),
                INITIAL_SPEED * std::sin((this->player->getGun()->getRotation() - 90.f) * M_PI / 180.f)
            },
            false,
            1.f,
            Constants::GRAVITY
        }
    );
    this->player->getGun()->setLastShotTime(std::chrono::steady_clock::now());

    this->bombList.push_back(bomb);
	this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(bomb));
	this->objectManager.addNewObject(bomb);

    return false;
}

bool GunShotSubscriber::isValid() const noexcept {
    return !this->isToBeDeleted();
}
