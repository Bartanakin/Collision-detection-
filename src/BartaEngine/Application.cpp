#include "pch.h"
#include "Application.h"
#include "Collisions/CollisionDetectionStrategyInterface.h"
#include "Events/Events/CollisionEvent.h"

Barta::Application::Application(
	std::unique_ptr<BartaGraphicsBridgeInterface> graphicsBridge,
	std::unique_ptr<BartaEventLoggerInterface> eventLogger,
	std::unique_ptr<BartaEventLoggerInterface> postDynamicsEventLogger,
	std::unique_ptr<ObjectManagerInterface> objectManager,
	std::unique_ptr<TimerInterface> timer,
	std::unique_ptr<DynamicsUpdateStrategyInterface> dynamicsUpdateStrategy,
	std::unique_ptr<CollisionTestExecutorInterface> collisionTestExecutor
):
	graphicsBridge(std::move(graphicsBridge)),
	eventLogger(std::move(eventLogger)),
	postDynamicsEventLogger(std::move(postDynamicsEventLogger)),
	objectManager(std::move(objectManager)),
	timer(std::move(timer)),
	dynamicsUpdateStrategy(std::move(dynamicsUpdateStrategy)),
	collisionTestExecutor(std::move(collisionTestExecutor)) {
}

Barta::Application::~Application() {}

void Barta::Application::run(){
	this->graphicsBridge->createWindow( Vector2f( 700.f, 700.f ), "Hello world!" );
	while( this->graphicsBridge->logEvents( *(this->eventLogger) )){
		this->timer->restart();
		while( !timer->finished() ){
			this->checkLogic();
			for (const auto& testResult : this->collisionTestExecutor->executeTests(this->objectManager->getCollidableList())) {
				this->eventLogger->logEvent(CollisionEvent(testResult, timer->getCurrentDeltaTime()));
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