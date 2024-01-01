#include "StageOne.h"
#include "Graphics/SpriteBuilder/RectangleWithColorsSpriteBuilder.h"

StageOne::StageOne(
    ListManager& listManager,
    Barta::ObjectManagerInterface& objectManager,
    ObjectsRepository objectsRepository
) noexcept
    : deleteWatch(false),
      listManager(listManager),
      objectManager(objectManager),
      objectsRepository(objectsRepository)
{}

void StageOne::setPlayerPosition(Player *player) const {
    player->setPosition(Barta::Vector2f(300.f, 600.f - 60.f));
}

void StageOne::prepareStage() {
    this->deleteWatch = false;
    auto ball1 = new Ball(
        Barta::Vector2f(150.f, 200.f),
        false,
        Ball::BallSize::MEDIUM
    );
    this->listManager.addObject(ball1);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball1));
    this->objectManager.addNewObject(ball1);

    this->objectsRepository.addWalls();
}

void StageOne::clearStage() {
    this->deleteWatch = true;

    for (auto& bomb : listManager.Barta::StaticObjectManager<Bomb>::getList()) {
        bomb->markToBeDeleted();
    }

    for (auto& ball : listManager.Barta::StaticObjectManager<Ball>::getList()) {
        ball->markToBeDeleted();
    }

    for (auto& wall : listManager.Barta::StaticObjectManager<Wall>::getList()) {
        wall->markToBeDeleted();
    }

    this->listManager.StaticObjectManager<Ball>::reduceDeleted();
    this->listManager.StaticObjectManager<Wall>::reduceDeleted();
    this->listManager.StaticObjectManager<Bomb>::reduceDeleted();
    this->objectManager.reduceDeleted();
}
