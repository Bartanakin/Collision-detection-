//
// Created by barta on 29/12/2023.
//

#include "PlayerHitSubscriber.h"
Subscribers::PlayerHitSubscriber::PlayerHitSubscriber(
    bool *deleteWatch,
    PostDynamicEventLogger& postDynamicEventLogger
) noexcept
    : Barta::DeletableObject(deleteWatch),
      postDynamicEventLogger(postDynamicEventLogger)
{}
bool Subscribers::PlayerHitSubscriber::isValid() const noexcept {
    return !this->isToBeDeleted();
}
bool Subscribers::PlayerHitSubscriber::handle(Events::PlayerBall &event) {
    // TODO add runnning subscribers until an empty queue
    this->postDynamicEventLogger.logEvent(StageChangeEvent(StageChangeEvent::StageID::NO_STAGE));
    this->postDynamicEventLogger.logEvent(SceneChangeEvent(SceneChangeEvent::SceneType::LOBBY));
    this->postDynamicEventLogger.logEvent(FlashMessageEvent(
        "You've lost. Evade the balls more carefully!",
        4s
    ));

    return false;
}
