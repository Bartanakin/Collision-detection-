#pragma once
#include"BartaEvent.h"
#include"EventSubscriberInterface.h"

namespace Barta{

	class BartaEventLoggerInterface{
	public:
		BartaEventLoggerInterface() = default;
		virtual ~BartaEventLoggerInterface() = default;

		virtual void logEvent( BartaEvent* event ) = 0;
		virtual void logSubscriber( EventSubscriberInterface* subscriber ) = 0;
		virtual void runSubscription() = 0;
	};
}

