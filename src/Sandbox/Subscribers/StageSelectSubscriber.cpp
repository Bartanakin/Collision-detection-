//
// Created by barta on 29/12/2023.
//

#include "StageSelectSubscriber.h"
StageSelectSubscriber::StageSelectSubscriber(
    bool *deleteWatch,
    std::vector<StageSelectButton *> stageButtons,
    PostDynamicEventLogger &postDynamicEventLogger
) noexcept
    : Barta::DeletableObject(deleteWatch),
      stageButtons(std::move(stageButtons)),
      postDynamicEventLogger(postDynamicEventLogger)
{}

bool StageSelectSubscriber::handle(Barta::LeftClickEvent &event) {
    for (auto& stageButton : this->stageButtons) {
        if (stageButton->getHitbox()->isWithin(event.getPosition())) {
            this->postDynamicEventLogger.logEvent(SceneChangeEvent(SceneChangeEvent::SceneType::GAME));
            this->postDynamicEventLogger.logEvent(StageChangeEvent(stageButton->getStageId()));

            return true;
        }
    }

    return false;
}
bool StageSelectSubscriber::isValid() const noexcept {
    return !this->isToBeDeleted();
}
