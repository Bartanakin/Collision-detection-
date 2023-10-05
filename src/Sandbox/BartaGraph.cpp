#include "BartaGraph.h"
#include"Graphics/SFML_GraphicsBridge.h"
#include"Geometrics/SFML_Transformable.h"
#include"Geometrics/Math/BartaMathLibrary.h"
#include"BartaObjectManager.h"
#include"Subscribers/ChangeBallColorSubscriber.h"
#include"Subscribers/Collisions/ChangeBallColorOnCollisionSubscriber.h"
#include"Subscribers/Collisions/ChangeBallOnCollisionWithAABB.h"
#include"Dynamics/ConstVelocityDynamicsUpdateStrategy.h"
#include"Collisions/CollisionDetectionStrategies/StaticCollisionDetectionStrategy.h"
#include"Collisions/CollisionDetectionStrategies/DynamicCollisionDetectionStrategy.h"
#include"Collisions/CollisionExecutors/CollisionTestExecutor.h"
#include"Collisions/CollisionExecutors/FilterNoCollisionResultsDecorator.h"
#include"Collisions/CollisionExecutors/FilterCollisionsOvertimeDecorator.h"
#include "Events/Subscribers/CollisionResponseSubscriber.h"
#include "Events/Subscribers/DynamicsChangeSubscriber.h"


void BartaGraph::checkLogic() {
}


BartaGraph::BartaGraph(std::unique_ptr<Barta::TimerInterface> timer)
	: Application( 
		std::make_unique<Barta::SFML_GraphicsBridge>(),
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
    block(nullptr),
    upperBound(nullptr),
    leftBound(nullptr),
    bottomBound(nullptr),
    rightBound(nullptr)
{
	this->ball1 = new Ball(
		Barta::Vector2f(380.f, 360.f),
		Barta::DynamicsDTO(Barta::Vector2f(-48.f, -150.f), false)
	);
	this->objectManager->addCollidableObject(static_cast<Barta::CollisionAwareInterface*>(ball1));
	this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball1));
	this->objectManager->addNewObject(ball1);

	this->ball2 = new Ball(
		Barta::Vector2f(180.f, 160.f),
		Barta::DynamicsDTO(Barta::Vector2f(150.f, 60.f), false)
	);
	this->objectManager->addCollidableObject(static_cast<Barta::CollisionAwareInterface*>(ball2));
	this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball2));
	this->objectManager->addNewObject(ball2);

	this->ball3 = new Ball(
		Barta::Vector2f(120.f, 300.f),
		Barta::DynamicsDTO(Barta::Vector2f(170.f, -84.f), false)
	);
	this->objectManager->addCollidableObject(static_cast<Barta::CollisionAwareInterface*>(ball3));
	this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(ball3));
	this->objectManager->addNewObject(ball3);
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

	this->eventLogger->logSubscriber(std::unique_ptr<Barta::CollisionEventSubscriberInterface>(new Barta::CollisionResponseSubscriber(*this->postDynamicsEventLogger)));
	this->postDynamicsEventLogger->logSubscriber(std::unique_ptr<Barta::DynamicsChangeSubscriberInterface>(new Barta::DynamicsChangeSubscriber()));
}

BartaGraph::~BartaGraph(){

}

std::unique_ptr<Barta::TransformableInterface> BartaGraph::createNewTransformableInstance(){
	return std::unique_ptr<Barta::TransformableInterface>(new Barta::SFML_Transformable());
}

