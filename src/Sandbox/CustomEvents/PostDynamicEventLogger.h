#pragma once

#include "BallCreateEvent.h"
#include "FlashMessageEvent.h"
#include "SceneChangeEvent.h"
#include "StageChangeEvent.h"
#include <Events/BartaEventLoggerInterface.h>

typedef Barta::EventMatcher<
    BallCreateEvent,
    SceneChangeEvent,
    StageChangeEvent,
    FlashMessageEvent
> PostDynamicEventLogger;

