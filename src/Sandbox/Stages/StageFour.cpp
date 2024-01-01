//
// Created by barta on 29/12/2023.
//

#include "StageFour.h"
#include "Graphics/SpriteBuilder/RectangleWithColorsSpriteBuilder.h"

StageFour::StageFour(
    ListManager& listManager,
    Barta::ObjectManagerInterface& objectManager,
    ObjectsRepository objectsRepository
    ) noexcept
    : deleteWatch(false),
      listManager(listManager),
      objectManager(objectManager),
      objectsRepository(objectsRepository)
{}

void StageFour::setPlayerPosition(Player *player) const {
    player->setPosition(Barta::Vector2f(540.f, 600.f - 60.f));
}

void StageFour::prepareStage() {
    this->deleteWatch = false;

    auto ball0 = new Ball(
        Barta::Vector2f(460.f, 400.f),
        true,
        Ball::BallSize::MEDIUM
    );
    ball0->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(ball0);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball0));
    this->objectManager.addNewObject(ball0);

    auto ball1 = new Ball(
        Barta::Vector2f(120.f, 400.f),
        false,
        Ball::BallSize::VERY_SMALL
    );
    ball1->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(ball1);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball1));
    this->objectManager.addNewObject(ball1);

    auto ball2 = new Ball(
        Barta::Vector2f(310.f, 400.f),
        true,
        Ball::BallSize::VERY_SMALL
    );
    ball2->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(ball2);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball2));
    this->objectManager.addNewObject(ball2);

    auto merger = Barta::SpriteMerger();
    auto builder = Barta::RectangleWithColorsSpriteBuilder();

    builder.setVertex1({0.f, 0.f});
    builder.setSize({40.f, 220.f});
    builder.setAllColors(Wall::WALL_COLOR);

    merger.addRectanglewithColors(builder.build());

    auto resource = merger.merge(false);
    auto wall1 = new Wall(
        {330.f, 380.f},
        {{0.f, 0.f}, {40.f, 220.f}},
        resource
    );
    wall1->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(wall1);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(wall1));
    this->objectManager.addNewObject(wall1);


    this->objectsRepository.addWalls();
}

void StageFour::clearStage() {
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
