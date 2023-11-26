#pragma once
#include <ReduceableList.h>
#include <StaticObjectManager.h>
#include <Collisions/StaticCollisionLogger.h>
#include <Collisions/CollisionExecutors/StaticCollisionTestExecutor.h>
#include <Events/BartaEventLoggerInterface.h>
#include "Ball.h"
#include "Bomb.h"
#include "Wall.h"

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
    Bomb, Wall
> StaticCollisionLogger; // <--

typedef Barta::EventMatcher<
    Barta::SCollisionEvent<Ball, Bomb>,
    Barta::SCollisionEvent<Ball, Wall>,
    Barta::SCollisionEvent<Ball, Ball>,
    Barta::SCollisionEvent<Bomb, Wall>
> CollisionEventsLogger; // <--


typedef Barta::StaticObjectManager<
    Ball,
    Wall,
    Bomb
> ListManager; // <--
