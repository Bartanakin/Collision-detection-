#pragma once

#include "BallBombSubscriber.h"
#include "../../ListsDefinitions.h"
#include <BartaObjectManager.h>
#include "../../CustomEvents/PostDynamicEventLogger.h"

namespace Subscribers {
    class BallHit: public BallBomb {

        static const Barta::Vector2f d; // vector sloped by 45 degrees up to the axis X

        public:
        BallHit(
            PostDynamicEventLogger& postDynamicEventLogger,
            const Barta::Vector2f gravity
        ) noexcept;
        virtual ~BallHit() noexcept = default;

        virtual bool handle(Events::BallBomb& event);

        virtual bool isValid() const noexcept;

        private:
        PostDynamicEventLogger& postDynamicEventLogger;
        const Barta::Vector2f gravity;
    };
};