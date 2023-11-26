#include "BartaGraph.h"
#include"Graphics/SFML_GraphicsBridge.h"
#include"Geometrics/SFML_Transformable.h"
#include"Geometrics/Math/BartaMathLibrary.h"
#include"BartaObjectManager.h"
#include"Dynamics/ConstVelocityDynamicsUpdateStrategy.h"
#include"Collisions/CollisionDetectionStrategies/StaticCollisionDetectionStrategy.h"
#include"Collisions/CollisionDetectionStrategies/DynamicCollisionDetectionStrategy.h"
#include"Collisions/CollisionExecutors/CollisionTestExecutor.h"
#include"Collisions/CollisionExecutors/FilterNoCollisionResultsDecorator.h"
#include"Collisions/CollisionExecutors/FilterCollisionsOvertimeDecorator.h"
#include "Events/Subscribers/CollisionResponseSubscriber.h"
#include "Events/Subscribers/StaticCollisionResponseSubscriber.h"
#include "Events/Subscribers/DynamicsChangeSubscriber.h"
#include "SimpleResourceContainer.h"
#include "Subscribers/PlayerMoveSubscriber.h"
#include "Subscribers/GunMoveSubscriber.h"
#include "Subscribers/DynamicsChangeSubscriberProxy.h"
#include "Subscribers/GunShotSubscriber.h"
#include "Subscribers/Collisions/BombCollisionSubscriber.h"
#include "ReloadMarker.h"
#include "Subscribers/Collisions/BallWallSubscriber.h"
#include "Subscribers/Collisions/WallBounceSubscriber.h"
#include "Subscribers/Collisions/BallHitSubscriber.h"
#include "CustomEvents/BallCreateEvent.h"
#include "Subscribers/BallCreateSubscriber.h"

const Barta::Vector2f gravity = {0.f, 250.f};

BartaGraph::BartaGraph(std::unique_ptr<Barta::TimerInterface> timer)
	: Application( 
		std::make_unique<Barta::SFML_GraphicsBridge>(
            std::make_unique<SimpleResourceContainer>()
        ),
		std::make_unique<Barta::BartaEventLoggerInterface>(),
		std::make_unique<Barta::BartaEventLoggerInterface>(),
		std::make_unique<Barta::BartaObjectManager>(),
		std::move(timer),
		std::make_unique<Barta::ConstVelocityDynamicsUpdateStrategy>(),
		std::make_unique<Barta::FilterCollisionsOvertimeDecorator>(
			std::make_unique<Barta::FilterNoCollisionResultsDecorator>(
				std::make_unique<Barta::CollisionTestExecutor>(
                    std::make_unique<Barta::DynamicCollisionDetectionStrategy>(std::make_unique<Barta::BartaMathLibrary>(), *timer)
                    // std::make_unique<Barta::StaticCollisionDetectionStrategy>(std::make_unique<Barta::BartaMathLibrary>())
				)
			),
			*timer
		)
		
	),
    postDynamicEventLogger(std::make_unique<PostDynamicEventLogger>()),
    ball1(nullptr),
    ball2(nullptr),
    ball3(nullptr),
    player(nullptr),
    upperBound(nullptr),
    leftBound(nullptr),
    bottomBound(nullptr),
    rightBound(nullptr),
    collisionEventsLogger({}),
    collisionExecutor(
        {{std::make_unique<Barta::DynamicCollisionDetectionStrategy>(std::make_unique<Barta::BartaMathLibrary>(), *this->timer)}},
        *this->timer
    ),
    objectLists({})
{
	this->ball1 = new Ball(
		Barta::Vector2f(200.f, 559.f),
        false,
        Ball::BallSize::SMALL,
        gravity
	);
    this->objectLists.addObject(this->ball1);
	this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball1));
	this->objectManager->addNewObject(ball1);

	// this->ball2 = new Ball(
	// 	Barta::Vector2f(180.f, 231.f),
	// 	Barta::DynamicsDTO(Barta::Vector2f(-20.f, 0.f), false, 1.0f, gravity),
    //     Ball::BallSize::MEDIUM
	// );
    // this->objectLists.addObject(this->ball2);
	// this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball2));
	// this->objectManager->addNewObject(ball2);

	// this->ball3 = new Ball(
	// 	Barta::Vector2f(120.f, 300.f),
	// 	Barta::DynamicsDTO(Barta::Vector2f(170.f, -84.f), false, 4.0f, gravity),
    //     Ball::BallSize::LARGE
	// );
    // this->objectLists.addObject(this->ball3);
	// this->objectManager->addCollidableObject(static_cast<Barta::CollisionAwareInterface*>(ball3));
	// this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball3));
	// this->objectManager->addNewObject(ball3);

    Gun* gun = new Gun();

	this->player = new Player(
		Barta::Vector2f(300.f, 600.f - 60.f),
		Barta::DynamicsDTO({}, false, 1.0f),
        gun
	);
	this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(player));
	this->objectManager->addNewObject(player);

	this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(gun));
    this->objectManager->addNewObject(gun);

	this->upperBound = new GiantBlock({100.f, -400.f});
    this->objectLists.addObject(this->upperBound);
	this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(this->upperBound));
	this->objectManager->addNewObject(this->upperBound);

	this->rightBound = new GiantBlock({600.f, 100.f});
    this->objectLists.addObject(this->rightBound);
	this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(this->rightBound));
	this->objectManager->addNewObject(this->rightBound);

	this->bottomBound = new GiantBlock({100.f, 600.f});
    this->objectLists.addObject(this->bottomBound);
	this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(this->bottomBound));
	this->objectManager->addNewObject(this->bottomBound);

	this->leftBound = new GiantBlock({-400.f, 100.f});
    this->objectLists.addObject(this->leftBound);
	this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(this->leftBound));
	this->objectManager->addNewObject(this->leftBound);

	auto reloadMarker = new ReloadMarker(gun);
	this->objectManager->addNewObject(reloadMarker);

	this->eventLogger->logSubscriber(std::unique_ptr<Barta::KeyPressedSubscriberInterface>(new PlayerMoveSubscriber(this->player)));
	this->eventLogger->logSubscriber(std::unique_ptr<Barta::KeyReleasedSubscriberInterface>(new PlayerMoveSubscriber(this->player)));

    this->eventLogger->logSubscriber(std::unique_ptr<Barta::KeyPressedSubscriberInterface>(new GunMoveSubscriber(gun)));
    this->eventLogger->logSubscriber(std::unique_ptr<Barta::KeyReleasedSubscriberInterface>(new GunMoveSubscriber(gun)));

	this->postDynamicsEventLogger->logSubscriber(std::make_unique<Barta::DynamicsChangeSubscriber>());
	this->eventLogger->logSubscriber(std::unique_ptr<Barta::KeyPressedSubscriberInterface>(new GunShotSubscriber(
        this->player,
        this->objectLists.StaticObjectManager<Bomb>::getList(),
        gravity,
        *this->objectManager
    )));

    this->collisionEventsLogger.Barta::EventMatcher<Events::BallWall>::logSubscriber(
        std::make_unique<Subscribers::WallBounce>(*this->postDynamicsEventLogger)
    );
    this->collisionEventsLogger.Barta::EventMatcher<Events::BombWall>::logSubscriber(
        std::make_unique<BombCollisionSubscriber>()
    );
    this->collisionEventsLogger.Barta::EventMatcher<Events::BallBomb>::logSubscriber(
        std::make_unique<Subscribers::BallHit>(
            *this->postDynamicEventLogger,
            gravity
        )
    );
    this->postDynamicEventLogger->logSubscriber(
        std::unique_ptr<BallCreateSubscriberInterface>(new BallCreateSubscriber(
            *this->objectManager,
            this->objectLists.StaticObjectManager<Ball>::getList()
        ))
    );
}

void BartaGraph::checkLogic() {
    StaticCollisionLogger().executeAndLog<CollisionEventsLogger, ListManager, CollisionCoreExecutor>(
        this->collisionEventsLogger,
        this->objectLists,
        this->collisionExecutor,
        *this->timer
    );

    this->collisionEventsLogger.runSubscribers();
}

void BartaGraph::postDynamicUpdate() {
    Application::postDynamicUpdate();

    this->postDynamicEventLogger->runSubscribers();
}

void BartaGraph::preGarbageCollect() {
    this->objectLists.StaticObjectManager<Bomb>::reduceDeleted();
    this->objectLists.StaticObjectManager<Ball>::reduceDeleted();
}

BartaGraph::~BartaGraph() {}

std::unique_ptr<Barta::TransformableInterface> BartaGraph::createNewTransformableInstance(){
	return std::unique_ptr<Barta::TransformableInterface>(new Barta::SFML_Transformable());
}

