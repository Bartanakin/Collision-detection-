//
// Created by barta on 29/12/2023.
//

#include "StageThree.h"

StageThree::StageThree(
    ListManager& listManager,
    Barta::ObjectManagerInterface& objectManager,
    ObjectsRepository objectsRepository
    ) noexcept
    : deleteWatch(false),
      listManager(listManager),
      objectManager(objectManager),
      objectsRepository(objectsRepository)
{}

void StageThree::setPlayerPosition(Player *player) const {
    player->setPosition(Barta::Vector2f(500.f, 600.f - 60.f));
}

void StageThree::prepareStage() {
    this->deleteWatch = false;

    auto ball1 = new Ball(
        Barta::Vector2f(438.f, 480.f),
        false,
        Ball::BallSize::VERY_SMALL
    );
    ball1->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(ball1);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball1));
    this->objectManager.addNewObject(ball1);

    auto ball2 = new Ball(
        Barta::Vector2f(396.f, 465.f),
        false,
        Ball::BallSize::VERY_SMALL
    );
    ball2->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(ball2);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball2));
    this->objectManager.addNewObject(ball2);

    auto ball3 = new Ball(
        Barta::Vector2f(354.f, 445.f),
        false,
        Ball::BallSize::VERY_SMALL
    );
    ball3->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(ball3);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball3));
    this->objectManager.addNewObject(ball3);

    auto ball4 = new Ball(
        Barta::Vector2f(312.f, 420.f),
        false,
        Ball::BallSize::VERY_SMALL
    );
    ball4->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(ball4);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball4));
    this->objectManager.addNewObject(ball4);

    auto ball5 = new Ball(
        Barta::Vector2f(270.f, 390.f),
        false,
        Ball::BallSize::VERY_SMALL
    );
    ball5->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(ball5);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball5));
    this->objectManager.addNewObject(ball5);

    auto ball6 = new Ball(
        Barta::Vector2f(228.f, 355.f),
        false,
        Ball::BallSize::VERY_SMALL
    );
    ball6->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(ball6);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball6));
    this->objectManager.addNewObject(ball6);

    auto ball7 = new Ball(
        Barta::Vector2f(186.f, 315.f),
        false,
        Ball::BallSize::VERY_SMALL
    );
    ball7->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(ball7);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball7));
    this->objectManager.addNewObject(ball7);

    auto ball8 = new Ball(
        Barta::Vector2f(144.f, 265.f),
        false,
        Ball::BallSize::VERY_SMALL
    );
    ball8->setDeleteWatch(&this->deleteWatch);
    this->listManager.addObject(ball8);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball8));
    this->objectManager.addNewObject(ball8);


    this->objectsRepository.addWalls();
}

void StageThree::clearStage() {
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
