//
// Created by barta on 01/01/2024.
//

#include "FlashMessageSubscriber.h"
FlashMessageSubscriber::FlashMessageSubscriber(
    PostDynamicEventLogger &postDynamicEventLogger,
    Flash *flash
) noexcept
    : postDynamicEventLogger(postDynamicEventLogger),
      flash(flash)
{}

bool FlashMessageSubscriber::isValid() const noexcept {
    return true;
}

bool FlashMessageSubscriber::handle(FlashMessageEvent &event) {
    this->flash->setMessage(std::move(event.meesage), event.seconds);

    return false;
}
