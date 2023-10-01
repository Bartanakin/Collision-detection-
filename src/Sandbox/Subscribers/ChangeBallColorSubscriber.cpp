#include "ChangeBallColorSubscriber.h"

ChangeBallColorSubscriber::ChangeBallColorSubscriber( Ball& ball )
	: ball( ball ){}

bool ChangeBallColorSubscriber::handle( const Barta::LeftClickEvent& event ){
	if( !this->ball.getHitbox()->isWithin( event.getPosition() ) ){
		return false;
	}

	this->ball.setBallCollor( Barta::Resource::GREEN_BALL );

	return true;
}

bool ChangeBallColorSubscriber::isValid() const noexcept{
	return true;
}
