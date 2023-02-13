#pragma once
#include "BartaEventLoggerInterface.h"
#include<list>

namespace Barta{

    class SimpleEventLogger : public BartaEventLoggerInterface{
    public:
        SimpleEventLogger() noexcept = default;
        virtual ~SimpleEventLogger();
        SimpleEventLogger( const SimpleEventLogger& ) noexcept = delete;

        void logEvent( BartaEvent* event );

        void logSubscriber( EventSubscriberInterface* subscriber );

        void runSubscription();

    private:
        std::list<BartaEvent*> events;
        std::list<EventSubscriberInterface*> subscribers;

        void clearSubscriberList();

        void clearEvents();
    };
}

