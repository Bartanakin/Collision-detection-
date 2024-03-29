#pragma once

#include "BallWallSubscriber.h"

namespace Subscribers {
    class WallBounce:
        public BallWall,
        public Barta::DeletableObject {
        public:
        WallBounce(
            bool* deleteWatch,
            Barta::BartaEventLoggerInterface& eventLogger
        ) noexcept;
        virtual ~WallBounce() noexcept = default;

        virtual bool handle(Events::BallWall& event);

        virtual bool isValid() const noexcept;

        private:
        Barta::BartaEventLoggerInterface& eventLogger;
        Barta::StaticCollisionResponseSubscriberType<Ball, Wall> innerSubscriber;
    };
};