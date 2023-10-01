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


BartaGraph::BartaGraph( Barta::TimerInterface* const timer )
	: Application( 
		new Barta::SFML_GraphicsBridge(),
		new Barta::BartaEventLoggerInterface(),
		new Barta::BartaEventLoggerInterface(),
		new Barta::BartaObjectManager(),
		timer,
		new Barta::ConstVelocityDynamicsUpdateStrategy(),
		new Barta::FilterCollisionsOvertimeDecorator(
			std::move(std::unique_ptr<Barta::CollisionTestExecutorInterface>(new Barta::FilterNoCollisionResultsDecorator(
				std::move(std::unique_ptr<Barta::CollisionTestExecutorInterface>(new Barta::CollisionTestExecutor(
					std::move(std::unique_ptr<Barta::CollisionDetectionStrategyInterface>(
						new Barta::DynamicCollisionDetectionStrategy(new Barta::BartaMathLibrary(), *timer)
						//new Barta::StaticCollisionDetectionStrategy(new Barta::BartaMathLibrary())
					))
				)))
			))),
			*timer
		)
		
	)
{
	//#define TEST_CASE 0
	//#define TEST_CASE 1
	//#define TEST_CASE 2
	//#define TEST_CASE 3
	//#define TEST_CASE 4
	#define TEST_CASE 5
	//#define TEST_CASE 6

	// circle - circle
	#if TEST_CASE == 0
		this->ball1 = new Ball(
			Barta::Vector2f(0.f, 0.f),
			Barta::DynamicsDTO(Barta::Vector2f(12.f, 12.f))
		);
		this->eventLogger->logSubscriber( std::unique_ptr<Barta::LeftClickEventSubscriberInterface>(new ChangeBallColorSubscriber( *ball1 )) );
		this->objectManager->addDynamicsObject((Barta::DynamicsAwareInterface*) ball1);
		this->objectManager->addCollidableObject((Barta::CollisionAwareInterface*) ball1);
		this->objectManager->addNewObject( ball1 );

		this->ball2 = new Ball(
			Barta::Vector2f(200.f, 90.f),
			Barta::DynamicsDTO(Barta::Vector2f(-12.f, -12.f))
		);
		this->objectManager->addDynamicsObject((Barta::DynamicsAwareInterface*) ball2);
		this->eventLogger->logSubscriber(std::unique_ptr<Barta::LeftClickEventSubscriberInterface>(new ChangeBallColorSubscriber(*ball2)));
		this->objectManager->addCollidableObject((Barta::CollisionAwareInterface*) ball2);
		this->objectManager->addNewObject(ball2);

		this->eventLogger->logSubscriber(std::unique_ptr<Barta::CollisionEventSubscriberInterface>(new ChangeBallColorOnCollisionSubscriber(*ball1, *ball2)));
	#endif // 0

	// circle - AABB when the middle intersects the AABB
	#if TEST_CASE == 1
		this->ball3 = new Ball(
			Barta::Vector2f(161.f, 300.f),
			Barta::DynamicsDTO(Barta::Vector2f(0.f, -25.f))
		);
		this->objectManager->addCollidableObject((Barta::CollisionAwareInterface*) ball3);
		this->objectManager->addDynamicsObject((Barta::DynamicsAwareInterface*) ball3);
		this->objectManager->addNewObject(ball3);

		this->block = new Block(
			Barta::Vector2f(200.f, 100.f),
			Barta::DynamicsDTO(Barta::Vector2f(0.f, 0.f))
		);		
		this->objectManager->addCollidableObject((Barta::CollisionAwareInterface*) block);
		this->objectManager->addDynamicsObject((Barta::DynamicsAwareInterface*) block);
		this->objectManager->addNewObject(block);


		this->eventLogger->logSubscriber(std::unique_ptr<Barta::CollisionEventSubscriberInterface>(new ChangeBallOnCollisionWithAABB(*ball3, *block)));
	#endif // 1

	// circle - AABB when the middle doesn't intersect the AABB but a part of the circle does
	#if TEST_CASE == 2
		this->ball3 = new Ball(
			Barta::Vector2f(159.f, 300.f),
			Barta::DynamicsDTO(Barta::Vector2f(0.f, -25.f))
		);
		this->objectManager->addCollidableObject((Barta::CollisionAwareInterface*) ball3);
		this->objectManager->addDynamicsObject((Barta::DynamicsAwareInterface*) ball3);
		this->objectManager->addNewObject(ball3);

		this->block = new Block(
			Barta::Vector2f(200.f, 100.f),
			Barta::DynamicsDTO(Barta::Vector2f(0.f, 0.f))
		);
		this->objectManager->addCollidableObject((Barta::CollisionAwareInterface*) block);
		this->objectManager->addDynamicsObject((Barta::DynamicsAwareInterface*) block);
		this->objectManager->addNewObject(block);

		this->eventLogger->logSubscriber(std::unique_ptr<Barta::CollisionEventSubscriberInterface>(new ChangeBallOnCollisionWithAABB(*ball3, *block)));
	#endif // 2

	// circle - AABB when neither the middle intersects the AABB nor a part of the circle does but the corner does
	#if TEST_CASE == 3
	this->ball3 = new Ball(
		Barta::Vector2f(200.f, 250.f),
		Barta::DynamicsDTO(Barta::Vector2f(-25.f, -25.f))
	);
	this->objectManager->addCollidableObject((Barta::CollisionAwareInterface*) ball3);
	this->objectManager->addDynamicsObject((Barta::DynamicsAwareInterface*) ball3);
	this->objectManager->addNewObject(ball3);

	this->block = new Block(
		Barta::Vector2f(200.f, 100.f),
		Barta::DynamicsDTO(Barta::Vector2f(0.f, 0.f))
	);
	this->objectManager->addCollidableObject((Barta::CollisionAwareInterface*) block);
	this->objectManager->addDynamicsObject((Barta::DynamicsAwareInterface*) block);
	this->objectManager->addNewObject(block);

	this->eventLogger->logSubscriber(std::unique_ptr<Barta::CollisionEventSubscriberInterface>(new ChangeBallOnCollisionWithAABB(*ball3, *block)));
	#endif // 3

	// circle - AABB no intersection at all
	#if TEST_CASE == 4
	this->ball3 = new Ball(
		Barta::Vector2f(200.f, 265.f),
		Barta::DynamicsDTO(Barta::Vector2f(-25.f, -25.f))
	);
	this->objectManager->addCollidableObject((Barta::CollisionAwareInterface*) ball3);
	this->objectManager->addDynamicsObject((Barta::DynamicsAwareInterface*) ball3);
	this->objectManager->addNewObject(ball3);

	this->block = new Block(
		Barta::Vector2f(200.f, 100.f),
		Barta::DynamicsDTO(Barta::Vector2f(0.f, 0.f))
	);
	this->objectManager->addCollidableObject((Barta::CollisionAwareInterface*) block);
	this->objectManager->addDynamicsObject((Barta::DynamicsAwareInterface*) block);
	this->objectManager->addNewObject(block);


	this->eventLogger->logSubscriber(std::unique_ptr<Barta::CollisionEventSubscriberInterface>(new ChangeBallOnCollisionWithAABB(*ball3, *block)));
	#endif // 4
	// responses
	#if TEST_CASE == 5 || TEST_CASE == 6
#if TEST_CASE == 5
	this->ball1 = new Ball(
		Barta::Vector2f(380.f, 360.f),
		Barta::DynamicsDTO(Barta::Vector2f(-48.f, -150.f), false)
	);
	this->objectManager->addCollidableObject((Barta::CollisionAwareInterface*) ball1);
	this->objectManager->addDynamicsObject((Barta::DynamicsAwareInterface*) ball1);
	this->objectManager->addNewObject(ball1);

	this->ball2 = new Ball(
		Barta::Vector2f(180.f, 160.f),
		Barta::DynamicsDTO(Barta::Vector2f(150.f, 60.f), false)
	);
	this->objectManager->addCollidableObject((Barta::CollisionAwareInterface*) ball2);
	this->objectManager->addDynamicsObject((Barta::DynamicsAwareInterface*) ball2);
	this->objectManager->addNewObject(ball2);

	this->ball3 = new Ball(
		Barta::Vector2f(120.f, 300.f),
		Barta::DynamicsDTO(Barta::Vector2f(170.f, -84.f), false)
	);
	this->objectManager->addCollidableObject((Barta::CollisionAwareInterface*) ball3);
	this->objectManager->addDynamicsObject((Barta::DynamicsAwareInterface*) ball3);
	this->objectManager->addNewObject(ball3);
#endif
#if TEST_CASE == 6
	this->ball1 = new Ball(
		Barta::Vector2f(380.f, 360.f),
		Barta::DynamicsDTO(Barta::Vector2f(55.f, 0.f), false)
	);
	this->objectManager->addCollidableObject((Barta::CollisionAwareInterface*) ball1);
	this->objectManager->addDynamicsObject((Barta::DynamicsAwareInterface*) ball1);
	this->objectManager->addNewObject(ball1);
#endif
	this->upperBound = new GiantBlock({100.f, -400.f});
	this->objectManager->addCollidableObject((Barta::CollisionAwareInterface*) this->upperBound);
	this->objectManager->addDynamicsObject((Barta::DynamicsAwareInterface*) this->upperBound);
	this->objectManager->addNewObject(this->upperBound);

	this->rightBound = new GiantBlock({600.f, 100.f});
	this->objectManager->addCollidableObject((Barta::CollisionAwareInterface*) this->rightBound);
	this->objectManager->addDynamicsObject((Barta::DynamicsAwareInterface*) this->rightBound);
	this->objectManager->addNewObject(this->rightBound);

	this->bottomBound = new GiantBlock({100.f, 600.f});
	this->objectManager->addCollidableObject((Barta::CollisionAwareInterface*) this->bottomBound);
	this->objectManager->addDynamicsObject((Barta::DynamicsAwareInterface*) this->bottomBound);
	this->objectManager->addNewObject(this->bottomBound);

	this->leftBound = new GiantBlock({-400.f, 100.f});
	this->objectManager->addCollidableObject((Barta::CollisionAwareInterface*) this->leftBound);
	this->objectManager->addDynamicsObject((Barta::DynamicsAwareInterface*) this->leftBound);
	this->objectManager->addNewObject(this->leftBound);

	this->eventLogger->logSubscriber(std::unique_ptr<Barta::CollisionEventSubscriberInterface>(new Barta::CollisionResponseSubscriber(*this->postDynamicsEventLogger)));
	this->postDynamicsEventLogger->logSubscriber(std::unique_ptr<Barta::DynamicsChangeSubscriberInterface>(new Barta::DynamicsChangeSubscriber()));
	#endif // 5, 6 
}

BartaGraph::~BartaGraph(){

}

Barta::TransformableInterface* const BartaGraph::createNewTransformableInstance(){
	return new Barta::SFML_Transformable();
}

