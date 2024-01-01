#pragma once

#include <Events/TemplateEventSubscriber.h>

class FlashMessageEvent {
public:
    explicit FlashMessageEvent(
        std::string meesage,
        std::chrono::seconds seconds
    ) noexcept:
          meesage(std::move(meesage)),
          seconds(seconds)
    {}
    FlashMessageEvent(const FlashMessageEvent&) = delete;
    FlashMessageEvent(FlashMessageEvent&&) noexcept = default;
    FlashMessageEvent& operator=(const FlashMessageEvent&) = delete;
    ~FlashMessageEvent() noexcept = default;

    std::string meesage;
    std::chrono::seconds seconds;
};

SUBSCRIBER_INTERFACE_DEFINITION(FlashMessageEvent);

using FlashMessageSubscriberInterface = Barta::EventSubscriber<FlashMessageEvent>;
