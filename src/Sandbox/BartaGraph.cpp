#include "BartaGraph.h"
#include"Graphics/SFML_GraphicsBridge.h"
#include"Geometrics/SFML_Transformable.h"
#include"Geometrics/Math/BartaMathLibrary.h"
#include"BartaObjectManager.h"
#include"Subscribers/Collisions/ChangeBallColorOnCollisionSubscriber.h"
#include"Dynamics/ConstVelocityDynamicsUpdateStrategy.h"
#include"Collisions/CollisionDetectionStrategies/StaticCollisionDetectionStrategy.h"
#include"Collisions/CollisionDetectionStrategies/DynamicCollisionDetectionStrategy.h"
#include"Collisions/CollisionExecutors/CollisionTestExecutor.h"
#include"Collisions/CollisionExecutors/FilterNoCollisionResultsDecorator.h"
#include"Collisions/CollisionExecutors/FilterCollisionsOvertimeDecorator.h"
#include "Events/Subscribers/CollisionResponseSubscriber.h"
#include "Events/Subscribers/DynamicsChangeSubscriber.h"
#include "SimpleResourceContainer.h"
#include "Subscribers/PlayerMoveSubscriber.h"
#include "Subscribers/GunMoveSubscriber.h"
#include "Subscribers/Collisions/CollisionSubscriberProxy.h"
#include "Subscribers/DynamicsChangeSubscriberProxy.h"
#include "Subscribers/GunShotSubscriber.h"
#include "Subscribers/Collisions/BombCollisionSubscriber.h"

const Barta::Vector2f gravity = {0.f, 250.f};

void BartaGraph::checkLogic() {
    float sum = 0.f;
    const float groundY = 600.f;
    // sum += this->ball1->getDynamicsDTO().velocity.squareOfDistance({}) / 2.f;
    // sum += (groundY - this->ball1->getTransformable().getPosition().getY()) * gravity.getY();
    // sum += this->ball2->getDynamicsDTO().velocity.squareOfDistance({}) / 2.f;
    // sum += (groundY - this->ball2->getTransformable().getPosition().getY()) * gravity.getY();
    // sum += this->ball3->getDynamicsDTO().velocity.squareOfDistance({}) / 2.f;
    // sum += (groundY - this->ball3->getTransformable().getPosition().getY()) * gravity.getY();

    // std::cout << "E = " << sum << std::endl;
}

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
    ball1(nullptr),
    ball2(nullptr),
    ball3(nullptr),
    player(nullptr),
    upperBound(nullptr),
    leftBound(nullptr),
    bottomBound(nullptr),
    rightBound(nullptr),
    ballList(BallList()),
    bombList(BombList())
{
	this->ball1 = new Ball(
		Barta::Vector2f(380.f, 360.f),
		Barta::DynamicsDTO(Barta::Vector2f(-100.f, -100.f), false, 1.0f, gravity)
	);
	this->objectManager->addCollidableObject(static_cast<Barta::CollisionAwareInterface*>(ball1));
	this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball1));
	this->objectManager->addNewObject(ball1);

	this->ball2 = new Ball(
		Barta::Vector2f(180.f, 160.f),
		Barta::DynamicsDTO(Barta::Vector2f(150.f, 60.f), false, 1.0f, gravity)
	);
	this->objectManager->addCollidableObject(static_cast<Barta::CollisionAwareInterface*>(ball2));
	this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball2));
	this->objectManager->addNewObject(ball2);

	this->ball3 = new Ball(
		Barta::Vector2f(120.f, 300.f),
		Barta::DynamicsDTO(Barta::Vector2f(170.f, -84.f), false, 1.0f, gravity)
	);
	this->objectManager->addCollidableObject(static_cast<Barta::CollisionAwareInterface*>(ball3));
	this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball3));
	this->objectManager->addNewObject(ball3);

    Gun* gun = new Gun();

	this->player = new Player(
		Barta::Vector2f(300.f, 600.f - 60.f),
		Barta::DynamicsDTO({}, false, 1.0f),
        gun
	);
	this->objectManager->addCollidableObject(static_cast<Barta::CollisionAwareInterface*>(player));
	this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(player));
	this->objectManager->addNewObject(player);

	this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(gun));
    this->objectManager->addNewObject(gun);

	this->upperBound = new GiantBlock({100.f, -400.f});
	this->objectManager->addCollidableObject(static_cast<Barta::CollisionAwareInterface*>(this->upperBound));
	this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(this->upperBound));
	this->objectManager->addNewObject(this->upperBound);

	this->rightBound = new GiantBlock({600.f, 100.f});
	this->objectManager->addCollidableObject(static_cast<Barta::CollisionAwareInterface*>(this->rightBound));
	this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(this->rightBound));
	this->objectManager->addNewObject(this->rightBound);

	this->bottomBound = new GiantBlock({100.f, 600.f});
	this->objectManager->addCollidableObject(static_cast<Barta::CollisionAwareInterface*>(this->bottomBound));
	this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(this->bottomBound));
	this->objectManager->addNewObject(this->bottomBound);

	this->leftBound = new GiantBlock({-400.f, 100.f});
	this->objectManager->addCollidableObject(static_cast<Barta::CollisionAwareInterface*>(this->leftBound));
	this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(this->leftBound));
	this->objectManager->addNewObject(this->leftBound);

	this->eventLogger->logSubscriber(std::make_unique<CollisionSubscriberProxy>(
        this->player,
        this->bombList,
        std::make_unique<Barta::CollisionResponseSubscriber>(*this->postDynamicsEventLogger),
        std::make_unique<BombCollisionSubscriber>(
            this->bombList,
            std::vector<GiantBlock*>({
                this->upperBound,
                this->rightBound,
                this->leftBound,
                this->bottomBound
            }),
            this->ballList
        )
    ));
	this->eventLogger->logSubscriber(std::unique_ptr<Barta::KeyPressedSubscriberInterface>(new PlayerMoveSubscriber(this->player)));
	this->eventLogger->logSubscriber(std::unique_ptr<Barta::KeyReleasedSubscriberInterface>(new PlayerMoveSubscriber(this->player)));
	this->eventLogger->logSubscriber(std::unique_ptr<Barta::CollisionEventSubscriberInterface>(new PlayerMoveSubscriber(
        this->player,
        this->leftBound,
        this->rightBound
    )));
    this->eventLogger->logSubscriber(std::unique_ptr<Barta::KeyPressedSubscriberInterface>(new GunMoveSubscriber(gun)));
    this->eventLogger->logSubscriber(std::unique_ptr<Barta::KeyReleasedSubscriberInterface>(new GunMoveSubscriber(gun)));
	this->postDynamicsEventLogger->logSubscriber(std::make_unique<DynamicsChangeSubscriberProxy>(
        this->player,
        std::make_unique<Barta::DynamicsChangeSubscriber>()
    ));
	this->eventLogger->logSubscriber(std::unique_ptr<Barta::KeyPressedSubscriberInterface>(new GunShotSubscriber(
        this->player,
        this->bombList,
        gravity,
        *this->objectManager
    )));
}

BartaGraph::~BartaGraph() {}

std::unique_ptr<Barta::TransformableInterface> BartaGraph::createNewTransformableInstance(){
	return std::unique_ptr<Barta::TransformableInterface>(new Barta::SFML_Transformable());
}

