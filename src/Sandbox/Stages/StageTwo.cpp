//
// Created by barta on 26/12/2023.
//

#include "StageTwo.h"
#include "Graphics/SpriteBuilder/RectangleWithColorsSpriteBuilder.h"

StageTwo::StageTwo(
    ListManager& listManager,
    Barta::ObjectManagerInterface& objectManager,
    ObjectsRepository objectsRepository
) noexcept
    : deleteWatch(false),
      listManager(listManager),
      objectManager(objectManager),
      objectsRepository(objectsRepository)
{}

void StageTwo::setPlayerPosition(Player *player) const {
    player->setPosition(Barta::Vector2f(500.f, 600.f - 60.f));
}

void StageTwo::prepareStage() {
    this->deleteWatch = false;

    auto ball1 = new Ball(
        Barta::Vector2f(450.f, 110.f),
        false,
        Ball::BallSize::VERY_SMALL
    );
    ball1->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(ball1);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball1));
    this->objectManager.addNewObject(ball1);

    auto ball11 = new Ball(
        Barta::Vector2f(450.f, 110.f),
        true,
        Ball::BallSize::VERY_SMALL
    );
    ball11->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(ball11);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball11));
    this->objectManager.addNewObject(ball11);

    auto ball2 = new Ball(
        Barta::Vector2f(200.f, 200.f),
        false,
        Ball::BallSize::SMALL
    );
    ball2->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(ball2);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball2));
    this->objectManager.addNewObject(ball2);

    auto ball3 = new Ball(
        Barta::Vector2f(280.f, 200.f),
        false,
        Ball::BallSize::VERY_SMALL
    );
    ball3->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(ball3);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball3));
    this->objectManager.addNewObject(ball3);

    auto ball31 = new Ball(
        Barta::Vector2f(280.f, 200.f),
        true,
        Ball::BallSize::VERY_SMALL
    );
    ball31->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(ball31);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball31));
    this->objectManager.addNewObject(ball31);

    auto ball4 = new Ball(
        Barta::Vector2f(360.f, 200.f),
        false,
        Ball::BallSize::VERY_SMALL
    );
    ball4->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(ball4);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball4));
    this->objectManager.addNewObject(ball4);

    auto ball41 = new Ball(
        Barta::Vector2f(360.f, 200.f),
        true,
        Ball::BallSize::VERY_SMALL
    );
    ball41->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(ball41);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball41));
    this->objectManager.addNewObject(ball41);

    auto ball5 = new Ball(
        Barta::Vector2f(420.f, 200.f),
        false,
        Ball::BallSize::VERY_SMALL
    );
    ball5->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(ball5);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball5));
    this->objectManager.addNewObject(ball5);

    auto ball51 = new Ball(
        Barta::Vector2f(420.f, 200.f),
        true,
        Ball::BallSize::VERY_SMALL
    );
    ball51->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(ball51);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball51));
    this->objectManager.addNewObject(ball51);

    auto merger = Barta::SpriteMerger();
    auto builder = Barta::RectangleWithColorsSpriteBuilder();

    builder.setVertex1({0.f, 0.f});
    builder.setSize({300.f, 100.f});
    builder.setAllColors(Wall::WALL_COLOR);

    merger.addRectanglewithColors(builder.build());

    auto resource = merger.merge(false);
    auto wall1 = new Wall(
        {300.f, 300.f},
        {{0.f, 0.f}, {300.f, 100.f}},
        resource
    );
    wall1->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(wall1);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(wall1));
    this->objectManager.addNewObject(wall1);

    this->objectsRepository.addWalls();
}

void StageTwo::clearStage() {
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
