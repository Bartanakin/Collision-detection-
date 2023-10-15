#include "GunShotSubscriber.h"
#define M_PI 3.14159265358979323846f

constexpr const float GunShotSubscriber::INITIAL_SPEED = 400.f; 

GunShotSubscriber::GunShotSubscriber(
    Player* player,
    BombList &bombList,
    const Barta::Vector2f gravity,
    Barta::ObjectManagerInterface& objectManager
) noexcept :
    player(player),
    bombList(bombList),
    gravity(gravity),
    objectManager(objectManager)
{}

bool GunShotSubscriber::handle(Barta::KeyPressedEvent &event) {
    if (event.key != Barta::BartaKeyMap::SPACEBAR) {
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
            this->gravity
        }
    );

    this->bombList.push_back(bomb);
	this->objectManager.addCollidableObject(static_cast<Barta::CollisionAwareInterface*>(bomb));
	this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(bomb));
	this->objectManager.addNewObject(bomb);

    return false;
}

bool GunShotSubscriber::isValid() const noexcept {
    return true;
}
