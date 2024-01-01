#pragma once 

#include <Events/TemplateEventSubscriber.h>
#include <Events/Events/SCollisionEvent.h>
#include "../../Wall.h"
#include "../../Player.h"

namespace Events {
    using PlayerWall = Barta::SCollisionEvent<Player, Wall>;
}

SUBSCRIBER_INTERFACE_DEFINITION(Events::PlayerWall);

namespace Subscribers {
    using PlayerWall = Barta::EventSubscriber<Events::PlayerWall>;
};