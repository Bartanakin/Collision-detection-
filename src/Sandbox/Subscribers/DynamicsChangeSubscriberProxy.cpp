#include "DynamicsChangeSubscriberProxy.h"

DynamicsChangeSubscriberProxy::DynamicsChangeSubscriberProxy(
    Player *player,
    std::unique_ptr<Barta::DynamicsChangeSubscriberInterface> dynamicsChangeSubscriber
) noexcept :
    player(player),
    dynamicsChangeSubscriber(std::move(dynamicsChangeSubscriber))
 {}

bool DynamicsChangeSubscriberProxy::handle(Barta::DynamicsChangeEvent &event) {
    if (event.dynamicsAware == static_cast<Barta::DynamicsAwareInterface*>(this->player)) {
        return false;
    }

    return this->dynamicsChangeSubscriber->handle(event);
}

bool DynamicsChangeSubscriberProxy::isValid() const noexcept {
    return true;
}
