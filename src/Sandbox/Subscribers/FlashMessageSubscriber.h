#pragma once


#include "../CustomEvents/FlashMessageEvent.h"
#include "../CustomEvents/PostDynamicEventLogger.h"
#include "Objects/Flash.h"
class FlashMessageSubscriber
    : public FlashMessageSubscriberInterface {
public:
    FlashMessageSubscriber(
        PostDynamicEventLogger& postDynamicEventLogger,
        Flash* flash
    ) noexcept;
    FlashMessageSubscriber(const FlashMessageSubscriber&) = delete;
    FlashMessageSubscriber& operator=(const FlashMessageSubscriber&) = delete;
    ~FlashMessageSubscriber() noexcept = default;

    bool isValid() const noexcept override;
    bool handle(FlashMessageEvent &event) override;

private:
    PostDynamicEventLogger& postDynamicEventLogger;
    Flash* flash;
};
