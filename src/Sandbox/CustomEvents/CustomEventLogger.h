#pragma once

#include <Events/BartaEventLoggerInterface.h>
#include "GunShotEvent.h"

typedef Barta::EventMatcher<
    GunShotEvent
> CustomEventLogger;

