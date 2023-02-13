#include "Application.h"
#include "Collisions/CollisionDetectionStrategyInterface.h"

Barta::Application::Application(
	BartaGraphicsBridgeInterface* const graphicsBridge,
	BartaEventLoggerInterface* const eventLogger,
	ObjectManagerInterface* const objectManager,
	TimerInterface* const timer,
	DynamicsUpdateStrategyInterface* const dynamicsUpdateStrategy,
	CollisionDetectionStrategyInterface* const collisionDetectionStrategy
) :
	graphicsBridge( graphicsBridge ),
	eventLogger( eventLogger ),
	objectManager( objectManager ),
	timer( timer ),
	dynamicsUpdateStrategy( dynamicsUpdateStrategy ),
	collisionDetectionStrategy( collisionDetectionStrategy )
{}

Barta::Application::~Application(){
	delete this->graphicsBridge;
	delete this->eventLogger;
	delete this->objectManager;
	delete this->timer;
	delete this->dynamicsUpdateStrategy;
	delete this->collisionDetectionStrategy;
}

void Barta::Application::run(){
	this->graphicsBridge->createWindow( Vector2f( 600.f, 400.f ), "Hello world!" );
	while( this->graphicsBridge->logEvents( *(this->eventLogger) )){
		this->checkLogic();
		this->eventLogger->runSubscription();
		this->dynamicsUpdateStrategy->update( this->timer->getElapsedTime() );
		this->graphicsBridge->drawObjects( this->objectManager->getList() );
		this->objectManager->reduceDeleted();
	}
}