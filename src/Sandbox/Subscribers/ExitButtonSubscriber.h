#pragma once


#include "CustomEvents/PostDynamicEventLogger.h"
#include "Events/Events/LeftClickEvent.h"
class ExitButtonSubscriber
    : public Barta::LeftClickEventSubscriberInterface,
      public Barta::DeletableObject {
public:
    ExitButtonSubscriber(
        bool* deleteWatch,
        PostDynamicEventLogger& postDynamicEventLogger
    ) noexcept;
    ExitButtonSubscriber(const ExitButtonSubscriber&) = delete;
    ExitButtonSubscriber& operator=(const ExitButtonSubscriber&) = delete;
    ~ExitButtonSubscriber() noexcept override = default;

    bool handle(Barta::LeftClickEvent &event) override;
    bool isValid() const noexcept override;
public:
    PostDynamicEventLogger& postDynamicEventLogger;
};
