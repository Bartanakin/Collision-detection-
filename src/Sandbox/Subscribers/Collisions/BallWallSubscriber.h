#pragma once 

#include <Events/TemplateEventSubscriber.h>
#include <Events/Events/SCollisionEvent.h>
#include <Events/Subscribers/StaticCollisionResponseSubscriber.h>
#include "../../Wall.h"
#include "../../Ball.h"

namespace Events {
    using BallWall = Barta::SCollisionEvent<Ball, Wall>;
}

SUBSCRIBER_INTERFACE_DEFINITION(Events::BallWall);

namespace Subscribers {
    using BallWall = Barta::EventSubscriber<Events::BallWall>;
};