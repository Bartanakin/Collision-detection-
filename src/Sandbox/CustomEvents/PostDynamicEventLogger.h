#pragma once

#include <Events/BartaEventLoggerInterface.h>
#include "BallCreateEvent.h"

typedef Barta::EventMatcher<
    BallCreateEvent
> PostDynamicEventLogger;

