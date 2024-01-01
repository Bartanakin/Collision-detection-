#pragma once


#include "DeletableObject.h"
#include "Events/Events/LeftClickEvent.h"
class StopGameSubscriber
    : public Barta::LeftClickEventSubscriberInterface,
      public Barta::DeletableObject {
public:
    StopGameSubscriber(
        bool* deleteWatch,
        bool* isRunning_ptr
    ) noexcept;
    StopGameSubscriber(const StopGameSubscriber&) = delete;
    StopGameSubscriber& operator=(const StopGameSubscriber&) = delete;
    ~StopGameSubscriber() noexcept override = default;

    bool handle(Barta::LeftClickEvent &event) override;
    bool isValid() const noexcept override;
public:
    bool* isRunning_ptr;
};
