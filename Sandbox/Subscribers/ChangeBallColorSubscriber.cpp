#include "ChangeBallColorSubscriber.h"

ChangeBallColorSubscriber::ChangeBallColorSubscriber( Ball& ball )
	: ball( ball ){}

Barta::EventType ChangeBallColorSubscriber::getSupportedType() const noexcept{
	return Barta::EventType::LEFT_CLICK;
}

bool ChangeBallColorSubscriber::handle( const Barta::BartaEvent& event ){
	auto& leftClickEvent = ( const Barta::LeftClickEvent& )event;

	if( !this->ball.getHitbox()->isWithin( leftClickEvent.getPosition() ) ){
		return false;
	}

	this->ball.setBallCollor( Barta::Resource::GREEN_BALL );

	return true;
}

bool ChangeBallColorSubscriber::isValid() const noexcept{
	return true;
}
