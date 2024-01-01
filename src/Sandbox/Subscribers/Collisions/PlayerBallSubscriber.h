#pragma once 

#include <Events/TemplateEventSubscriber.h>
#include <Events/Events/SCollisionEvent.h>
#include "../../Ball.h"
#include "../../Player.h"

class Ball;
class Player;

namespace Events {
    using PlayerBall = Barta::SCollisionEvent<Player, Ball>;
}

SUBSCRIBER_INTERFACE_DEFINITION(Events::PlayerBall);

namespace Subscribers {
    using PlayerBall = Barta::EventSubscriber<Events::PlayerBall>;
};