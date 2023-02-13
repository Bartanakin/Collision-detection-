#include "ConstVelocityDynamicsUpdateStrategy.h"

Barta::ConstVelocityDynamicsUpdateStrategy::ConstVelocityDynamicsUpdateStrategy( float initialTime ) :
	savedTime( initialTime )
{}

Barta::ConstVelocityDynamicsUpdateStrategy::~ConstVelocityDynamicsUpdateStrategy(){}

// @Untracked dynamicsAware
void Barta::ConstVelocityDynamicsUpdateStrategy::subscribe( DynamicsAwareInterface* dynamicsAware ){
	this->objects.push_back( dynamicsAware );
}

void Barta::ConstVelocityDynamicsUpdateStrategy::update( const float updateTime ){
	const float deltaTime = updateTime - this->savedTime;
	this->savedTime = updateTime;

	auto i = this->objects.begin();
	while( i != this->objects.end() ){
		if( ( *i )->isToBeDeleted() ){
			i = this->objects.erase( i );
			continue;
		}

		( *i )->move( ( *i )->getDynamicsDTO().velocity * deltaTime );

		i++;
	}
}
