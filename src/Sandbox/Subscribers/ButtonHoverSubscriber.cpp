//
// Created by barta on 29/12/2023.
//

#include "ButtonHoverSubscriber.h"
ButtonHoverSubscriber::ButtonHoverSubscriber(
    bool *deleteWatch,
    std::vector<Button*> buttons
) noexcept
    : Barta::DeletableObject(deleteWatch),
      buttons(std::move(buttons))
{}

bool ButtonHoverSubscriber::isValid() const noexcept {
    return !this->isToBeDeleted();
}

bool ButtonHoverSubscriber::handle(Barta::MouseMoveEvent &event) {
    for (auto& button : this->buttons) {
        if (button->isToBeDeleted()) {
            continue;
        }

        button->setIsMouseHover(button->getHitbox()->isWithin(event.getPosition()));
    }

    return false;
}
