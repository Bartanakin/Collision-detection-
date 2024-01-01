#pragma once

#include "StageInterface.h"

class NoStage : public StageInterface {
public:
    NoStage() noexcept = default;

    void prepareStage() override {};
    void setPlayerPosition(Player *player) const override {};
    void clearStage() override {};
};
