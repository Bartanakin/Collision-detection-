#pragma once


#include "Button.h"
#include "../CustomEvents/StageChangeEvent.h"
class StageSelectButton
    : public Button {
public:
    StageSelectButton(
        Barta::Vector2f position,
        Barta::Vector2f testTranslation,
        Barta::Vector2f size,
        std::string string,
        StageChangeEvent::StageID stageId
    ) noexcept;
    ~StageSelectButton() noexcept = default;

    StageChangeEvent::StageID getStageId();

private:
    StageChangeEvent::StageID stageId;
};
