//
// Created by barta on 28/12/2023.
//

#include "ExitButtonSubscriber.h"

ExitButtonSubscriber::ExitButtonSubscriber(
    bool* deleteWatch,
    PostDynamicEventLogger &postDynamicEventLogger
) noexcept
    : Barta::DeletableObject(deleteWatch),
      postDynamicEventLogger(postDynamicEventLogger)
{}

bool ExitButtonSubscriber::handle(Barta::LeftClickEvent &event) {
    this->postDynamicEventLogger.logEvent(StageChangeEvent(StageChangeEvent::StageID::NO_STAGE));
    this->postDynamicEventLogger.logEvent(SceneChangeEvent(SceneChangeEvent::SceneType::LOBBY));

    return true;
}

bool ExitButtonSubscriber::isValid() const noexcept {
    return !this->isToBeDeleted();
}
