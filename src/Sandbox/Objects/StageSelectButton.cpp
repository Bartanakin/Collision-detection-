//
// Created by barta on 29/12/2023.
//

#include "StageSelectButton.h"

StageSelectButton::StageSelectButton(
    Barta::Vector2f position,
    Barta::Vector2f testTranslation,
    Barta::Vector2f size,
    std::string string,
    StageChangeEvent::StageID stageId
) noexcept
    : Button(position, testTranslation, size, std::move(string)),
      stageId(stageId)
{}

StageChangeEvent::StageID StageSelectButton::getStageId() {
    return this->stageId;
}
