#include "SimpleEventLogger.h"

Barta::SimpleEventLogger::~SimpleEventLogger(){
	auto i = this->subscribers.begin();
	while( i != this->subscribers.end() ){
		delete *i;

		i++;
	}

	this->clearEvents();
}

void Barta::SimpleEventLogger::clearEvents(){
	auto i2 = this->events.begin();
	while( i2 != this->events.end() ){
		delete* i2;

		i2++;
	}

	this->events.clear();
}

void Barta::SimpleEventLogger::logEvent( BartaEvent* event ){
	this->events.push_back( event );
}

void Barta::SimpleEventLogger::logSubscriber( EventSubscriberInterface* subscriber ){
	this->subscribers.push_back( subscriber );
}

void Barta::SimpleEventLogger::runSubscription(){
	for( auto subscriber : this->subscribers ){
		if( this->events.empty() ){
			return;
		}

		auto newEvents = std::list<BartaEvent*>();
		auto i = this->events.begin();
		while( i != this->events.end() ){
			if( subscriber->isValid() && subscriber->getSupportedType() == (*i)->getStaticType() ){
				if( subscriber->handle( **i ) ){
					delete *i;
				}
				else{
					newEvents.push_back( *i );
				}
			}

			i++;
		}

		this->events = newEvents;
	}

	this->clearSubscriberList();
	this->clearEvents();
}

void Barta::SimpleEventLogger::clearSubscriberList(){
	auto newSubscribers = std::list<EventSubscriberInterface*>();
	auto i = this->subscribers.begin();
	while( i != this->subscribers.end()){
		if( !(*i)->isValid() ){
			delete* i;
		}
		else{
			newSubscribers.push_back( *i );
		}

		i++;
	}

	this->subscribers = newSubscribers;
}
