#pragma once


#include "DeletableObject.h"
#include "Events/Events/MouseMoveEvent.h"
#include "Objects/Button.h"

class ButtonHoverSubscriber 
    : public Barta::MouseMoveSubscriberInterface,
      public Barta::DeletableObject {
public:
    ButtonHoverSubscriber(
        bool* deleteWatch,
        std::vector<Button*> buttons
    ) noexcept;
    ButtonHoverSubscriber(const ButtonHoverSubscriber&) = delete;
    ButtonHoverSubscriber& operator=(const ButtonHoverSubscriber&) = delete;
    ~ButtonHoverSubscriber() noexcept override = default;

    bool isValid() const noexcept override;
    bool handle(Barta::MouseMoveEvent &event) override;
private:
    std::vector<Button*> buttons;
};
