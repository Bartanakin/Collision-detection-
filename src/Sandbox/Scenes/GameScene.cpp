//
// Created by barta on 11/12/2023.
//

#include "GameScene.h"
#include "Events/Subscribers/DynamicsChangeSubscriber.h"
#include "Events/Subscribers/HitboxPositionCheckSubscriberProxy.h"
#include "Objects/Button.h"
#include "ReloadMarker.h"
#include "Subscribers/BallCreateSubscriber.h"
#include "Subscribers/ButtonHoverSubscriber.h"
#include "Subscribers/Collisions/BallBombSubscriber.h"
#include "Subscribers/Collisions/BallHitSubscriber.h"
#include "Subscribers/Collisions/BallWallSubscriber.h"
#include "Subscribers/Collisions/BombCollisionSubscriber.h"
#include "Subscribers/Collisions/PlayerBallSubscriber.h"
#include "Subscribers/Collisions/PlayerHitSubscriber.h"
#include "Subscribers/Collisions/PlayerWallCollisionSubscriber.h"
#include "Subscribers/Collisions/WallBounceSubscriber.h"
#include "Subscribers/ExitButtonSubscriber.h"
#include "Subscribers/GunMoveSubscriber.h"
#include "Subscribers/GunShotSubscriber.h"
#include "Subscribers/PlayerMoveSubscriber.h"

GameScene::GameScene(
    Barta::ObjectManagerInterface* objectManager,
    Barta::BartaEventLoggerInterface* eventLogger,
    Barta::BartaEventLoggerInterface* postDynamicsEventLogger,
    ListManager& objectLists,
    CollisionEventsLogger& collisionEventsLogger,
    PostDynamicEventLogger* postDynamicEventLogger,
    StageChangeEvent::StageID&selectedStage) noexcept
    : toBeDeleted(false),
      objectManager(objectManager),
      eventLogger(eventLogger),
      postDynamicsEventLogger(postDynamicsEventLogger),
      objectLists(objectLists),
      collisionEventsLogger(collisionEventsLogger),
      postDynamicEventLogger(postDynamicEventLogger),
      selectedStage(selectedStage),
      player_ptr(nullptr)
{
    this->postDynamicsEventLogger->logSubscriber(std::make_unique<Barta::DynamicsChangeSubscriber>());
}

void GameScene::load() {
    this->toBeDeleted = false;
    auto exitButton = new Button(
        {625.f, 625.f},
        {7.f, 17.f},
        {50.f, 50.f},
        "Menu"
    );
    exitButton->setDeleteWatch(&this->toBeDeleted);
    this->objectManager->addNewObject(exitButton);

    auto gun = new Gun();
    gun->setDeleteWatch(&this->toBeDeleted);

    this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(gun));
    this->objectManager->addNewObject(gun);

    auto player = new Player(
        Barta::Vector2f(300.f, 600.f - 60.f),
        Barta::DynamicsDTO({}, false, 1.0f),
        gun
    );
    this->player_ptr = player;

    player->setDeleteWatch(&this->toBeDeleted);
    this->objectLists.Barta::StaticObjectManager<Player>::addObject(player);
    this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(player));
    this->objectManager->addNewObject(player);

    auto reloadMarker = new ReloadMarker(gun);
    reloadMarker->setDeleteWatch(&this->toBeDeleted);
    this->objectManager->addNewObject(reloadMarker);

    this->eventLogger->logSubscriber(std::unique_ptr<Barta::KeyPressedSubscriberInterface>(
        new PlayerMoveSubscriber(&this->toBeDeleted, player)
    ));
    this->eventLogger->logSubscriber(std::unique_ptr<Barta::KeyReleasedSubscriberInterface>(
        new PlayerMoveSubscriber(&this->toBeDeleted, player)
    ));

    this->eventLogger->logSubscriber(std::unique_ptr<Barta::KeyPressedSubscriberInterface>(
        new GunMoveSubscriber(&this->toBeDeleted, gun)
    ));
    this->eventLogger->logSubscriber(std::unique_ptr<Barta::KeyReleasedSubscriberInterface>(
        new GunMoveSubscriber(&this->toBeDeleted, gun)
    ));

    this->eventLogger->logSubscriber(std::unique_ptr<Barta::KeyPressedSubscriberInterface>(new GunShotSubscriber(
        &this->toBeDeleted,
        player,
        this->objectLists.Barta::StaticObjectManager<Bomb>::getList(),
        *this->objectManager
    )));

    this->collisionEventsLogger.Barta::EventMatcher<Events::BallWall>::logSubscriber(
        std::make_unique<Subscribers::WallBounce>(&this->toBeDeleted, *this->postDynamicsEventLogger)
    );
    this->collisionEventsLogger.Barta::EventMatcher<Events::BombWall>::logSubscriber(
        std::make_unique<BombCollisionSubscriber>(&this->toBeDeleted)
    );
    this->collisionEventsLogger.Barta::EventMatcher<Events::PlayerWall>::logSubscriber(
        std::make_unique<Subscribers::PlayerWallCollisionSubscriber>(&this->toBeDeleted)
    );
    this->collisionEventsLogger.Barta::EventMatcher<Events::PlayerBall>::logSubscriber(
        std::make_unique<Subscribers::PlayerHitSubscriber>(&this->toBeDeleted, *this->postDynamicEventLogger)
    );
    this->collisionEventsLogger.Barta::EventMatcher<Events::BallBomb>::logSubscriber(
        std::make_unique<Subscribers::BallHit>(
            &this->toBeDeleted,
            *this->postDynamicEventLogger,
            this->objectLists.Barta::StaticObjectManager<Ball>::getList(),
            this->selectedStage
        )
    );
    this->postDynamicEventLogger->logSubscriber(
        std::unique_ptr<BallCreateSubscriberInterface>(new BallCreateSubscriber(
            &this->toBeDeleted,
            *this->objectManager,
            this->objectLists.StaticObjectManager<Ball>::getList()
        ))
    );
    this->eventLogger->logSubscriber(
        std::unique_ptr<Barta::LeftClickEventSubscriberInterface>(new Barta::HitboxPositionCheckSubscriberProxy<Barta::LeftClickEvent>(
            exitButton,
            std::unique_ptr<Barta::LeftClickEventSubscriberInterface>(new ExitButtonSubscriber(
                &this->toBeDeleted,
                *this->postDynamicEventLogger
            ))
        ))
    );
    this->eventLogger->logSubscriber(
        std::unique_ptr<Barta::MouseMoveSubscriberInterface>(new ButtonHoverSubscriber(
            &this->toBeDeleted,
            {exitButton}
        ))
    );
}

void GameScene::unload() {
    this->toBeDeleted = true;

    for (auto& player : this->objectLists.Barta::StaticObjectManager<Player>::getList()) {
        player->markToBeDeleted();
    }

    this->eventLogger->removeInvalid();
    this->postDynamicsEventLogger->removeInvalid();
    this->postDynamicEventLogger->removeInvalid();
    this->collisionEventsLogger.removeInvalid();
    this->objectLists.StaticObjectManager<Ball>::reduceDeleted();
    this->objectLists.StaticObjectManager<Wall>::reduceDeleted();
    this->objectLists.StaticObjectManager<Bomb>::reduceDeleted();
    this->objectLists.StaticObjectManager<Player>::reduceDeleted();

    this->objectManager->reduceDeleted();
}

GameScene::~GameScene() {
    this->GameScene::unload();
}

StageChangeEvent::StageID GameScene::getCurrentStageId() const {
    return this->selectedStage;
}

void GameScene::setCurrentStageId(StageChangeEvent::StageID stageId) {
    this->selectedStage = stageId;
}

Player *GameScene::getPlayer() {
    return this->player_ptr;
}
