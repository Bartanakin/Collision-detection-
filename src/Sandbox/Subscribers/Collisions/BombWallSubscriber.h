#pragma once

#include <Events/TemplateEventSubscriber.h>
#include <Events/Events/SCollisionEvent.h>
#include <Events/Subscribers/StaticCollisionResponseSubscriber.h>
#include "../../Wall.h"
#include "../../Bomb.h"

namespace Events {
    using BombWall = Barta::SCollisionEvent<Bomb, Wall>;
}

SUBSCRIBER_INTERFACE_DEFINITION(Events::BombWall);

namespace Subscribers {
    using BombWall = Barta::EventSubscriber<Events::BombWall>;
};