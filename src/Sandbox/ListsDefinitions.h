#pragma once
#include "Ball.h"
#include "Bomb.h"
#include "CustomEvents/SceneChangeEvent.h"
#include "CustomEvents/StageChangeEvent.h"
#include "Player.h"
#include "Subscribers/Collisions/PlayerWallSubscriber.h"
#include "Wall.h"
#include <Collisions/CollisionExecutors/StaticCollisionTestExecutor.h>
#include <Collisions/StaticCollisionLogger.h>
#include <Events/BartaEventLoggerInterface.h>
#include <ReduceableList.h>
#include <StaticObjectManager.h>

namespace Constants {
    const Barta::Vector2f GRAVITY = {0.f, 250.f};
}

typedef Barta::ReducibleList<std::vector<Ball*>> BallList;
typedef Barta::ReducibleList<std::vector<Bomb*>> BombList;
typedef Barta::ReducibleList<std::vector<Wall*>> WallList;

typedef Barta::SFilterCollisionsOvertimeDecorator<
    Barta::FilterNoCollisionDecorator<
        Barta::StaticCollisionTestExecutor
    >
> CollisionCoreExecutor; // <--

typedef Barta::StaticCollisionLogger<
    Ball, Bomb,
    Ball, Wall,
    Bomb, Wall,
    Player, Wall,
    Player, Ball
> StaticCollisionLogger; // <--

typedef Barta::EventMatcher<
    Barta::SCollisionEvent<Player, Wall>,
    Barta::SCollisionEvent<Ball, Bomb>,
    Barta::SCollisionEvent<Ball, Wall>,
    Barta::SCollisionEvent<Player, Ball>,
    Barta::SCollisionEvent<Bomb, Wall>
> CollisionEventsLogger; // <--


typedef Barta::StaticObjectManager<
    Ball,
    Wall,
    Bomb,
    Player
> ListManager; // <--
