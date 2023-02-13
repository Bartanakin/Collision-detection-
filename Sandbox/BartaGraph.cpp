#include "BartaGraph.h"
#include"log.h"
#include"Graphics/SFML_GraphicsBridge.h"
#include"Geometrics/SFML_Transformable.h"
#include"Events/SimpleEventLogger.h"
#include"BartaObjectManager.h"
#include"Subscribers/ChangeBallColorSubscriber.h"
#include"Dynamics/Timers/SFML_Timer.h"
#include"Dynamics/ConstVelocityDynamicsUpdateStrategy.h"
#include"Collisions/CollisionDetectionStrategies/StaticCollisionDetectionStrategy.h"

void BartaGraph::checkLogic(){
	if( ball1->getHitbox()->intersects( *ball2->getHitbox(), *this->collisionDetectionStrategy ) ){
		ball1->setBallCollor( Barta::Resource::GREEN_BALL );
	}
}


BartaGraph::BartaGraph()
	: Application( 
		new Barta::SFML_GraphicsBridge(),
		new Barta::SimpleEventLogger(),
		new Barta::BartaObjectManager(),
		new Barta::SFML_Timer(),
		new Barta::ConstVelocityDynamicsUpdateStrategy( Barta::SFML_Timer().getElapsedTime() ),
		new Barta::StaticCollisionDetectionStrategy()
	)
{
	this->ball1 = new Ball(
		Barta::Vector2f( 0., 0. ),
		Barta::DynamicsDTO( Barta::Vector2f( 25., 25. ) )
	);
	this->dynamicsUpdateStrategy->subscribe( (  Barta::DynamicsAwareInterface* )ball1 );
	this->eventLogger->logSubscriber( new ChangeBallColorSubscriber( *ball1 ) );
	this->objectManager->addNewObject( ball1 );

	this->ball2 = new Ball(
		Barta::Vector2f( 200., 200. ),
		Barta::DynamicsDTO( Barta::Vector2f( -25., -25. ) )
	);
	this->dynamicsUpdateStrategy->subscribe( ( Barta::DynamicsAwareInterface* )ball2 );
	this->eventLogger->logSubscriber( new ChangeBallColorSubscriber( *ball2 ) );
	this->objectManager->addNewObject( ball2 );
}

BartaGraph::~BartaGraph(){

}

Barta::TransformableInterface* const BartaGraph::createNewTransformableInstance(){
	return new Barta::SFML_Transformable();
}

