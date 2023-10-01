#include "pch.h"
#include "DynamicsChangeSubscriber.h"

bool Barta::DynamicsChangeSubscriber::handle(const DynamicsChangeEvent& event) {
    auto ptr = ((DynamicsAwareInterface*) (event.dynamicsAware));
    ((DynamicsAwareInterface*)(event.dynamicsAware))->setDynamicsDTO(event.newDynamics);

    return true;
}

bool Barta::DynamicsChangeSubscriber::isValid() const noexcept {
    return true;
}
