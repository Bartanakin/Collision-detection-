//
// Created by barta on 29/12/2023.
//

#include "StopGameSubscriber.h"
StopGameSubscriber::StopGameSubscriber(
    bool *deleteWatch,
    bool *isRunning_ptr
) noexcept
    : Barta::DeletableObject(deleteWatch),
      isRunning_ptr(isRunning_ptr)
{}
bool StopGameSubscriber::handle(Barta::LeftClickEvent &event) {
    *this->isRunning_ptr = false;

    return true;
}
bool StopGameSubscriber::isValid() const noexcept {
    return !this->isToBeDeleted();
}
