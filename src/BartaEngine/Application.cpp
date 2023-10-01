#include "pch.h"
#include "Application.h"
#include "Collisions/CollisionDetectionStrategyInterface.h"
#include "Events/Events/CollisionEvent.h"

Barta::Application::Application(
	BartaGraphicsBridgeInterface* const graphicsBridge,
	BartaEventLoggerInterface* const eventLogger,
	BartaEventLoggerInterface* const postDynamicsEventLogger,
	ObjectManagerInterface* const objectManager,
	TimerInterface* const timer,
	DynamicsUpdateStrategyInterface* const dynamicsUpdateStrategy,
	CollisionTestExecutorInterface* const collisionTestExecutor
):
	graphicsBridge(graphicsBridge),
	eventLogger(eventLogger),
	postDynamicsEventLogger(postDynamicsEventLogger),
	objectManager(objectManager),
	timer(timer),
	dynamicsUpdateStrategy(dynamicsUpdateStrategy),
	collisionTestExecutor(collisionTestExecutor) {
}

Barta::Application::~Application(){
	delete this->graphicsBridge;
	delete this->eventLogger;
	delete this->postDynamicsEventLogger;
	delete this->objectManager;
	delete this->timer;
	delete this->dynamicsUpdateStrategy;
	delete this->collisionTestExecutor;
}

void Barta::Application::run(){
	this->graphicsBridge->createWindow( Vector2f( 700.f, 700.f ), "Hello world!" );
	static int counter = 0;
	while( this->graphicsBridge->logEvents( *(this->eventLogger) )){
		this->timer->restart();
		while( !timer->finished() ){
			this->checkLogic();
			for (const auto& testResult : this->collisionTestExecutor->executeTests(this->objectManager->getCollidableList())) {
				counter++;
				this->eventLogger->logEvent(std::unique_ptr<const CollisionEvent>(new CollisionEvent(testResult, timer->getCurrentDeltaTime())));
			}

			this->eventLogger->runSubscribers();
			this->dynamicsUpdateStrategy->update(this->objectManager->getDynamicsList(), timer->getCurrentDeltaTime());
			this->postDynamicsEventLogger->runSubscribers();
			#if DEBUG_COLLISION_EVENT 
			std::cout << "CollisionEvent: " << CollisionEvent::stats << std::endl;
			CollisionEvent::reset();
			#endif

			this->timer->forward();
		}

		this->graphicsBridge->drawObjects( this->objectManager->getList() );


		this->objectManager->reduceDeleted();
	}
}