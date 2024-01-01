#pragma once


#include "CustomEvents/PostDynamicEventLogger.h"
#include "Events/Events/LeftClickEvent.h"
class InstructionButtonSubscriber
    : public Barta::LeftClickEventSubscriberInterface,
      public Barta::DeletableObject {
public:
    InstructionButtonSubscriber(
        bool* deleteWatch,
        PostDynamicEventLogger& postDynamicEventLogger
    ) noexcept;
    InstructionButtonSubscriber(const InstructionButtonSubscriber&) = delete;
    InstructionButtonSubscriber& operator=(const InstructionButtonSubscriber&) = delete;
    ~InstructionButtonSubscriber() noexcept override = default;

    bool handle(Barta::LeftClickEvent &event) override;
    bool isValid() const noexcept override;
public:
    PostDynamicEventLogger& postDynamicEventLogger;
};
