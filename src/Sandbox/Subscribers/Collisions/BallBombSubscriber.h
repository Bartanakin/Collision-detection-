#pragma once

#include <Events/TemplateEventSubscriber.h>
#include <Events/Events/SCollisionEvent.h>
#include <Events/Subscribers/StaticCollisionResponseSubscriber.h>
#include "../../Bomb.h"
#include "../../Ball.h"

namespace Events {
    using BallBomb = Barta::SCollisionEvent<Ball, Bomb>;
}

SUBSCRIBER_INTERFACE_DEFINITION(Events::BallBomb);

namespace Subscribers {
    using BallBomb = Barta::EventSubscriber<Events::BallBomb>;
};