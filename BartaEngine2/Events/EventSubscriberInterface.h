#pragma once
#include"BartaEvent.h"
namespace Barta{
	class EventSubscriberInterface{
	public:
		EventSubscriberInterface() = default;
		virtual ~EventSubscriberInterface() = default;

		virtual EventType getSupportedType() const noexcept = 0;
		/* Returns true if the event should be marked as handled */
		virtual bool handle( const BartaEvent& event ) = 0;
		virtual bool isValid() const noexcept = 0;
	};
}

