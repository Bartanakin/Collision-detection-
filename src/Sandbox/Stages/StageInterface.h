#pragma once

#include "../Player.h"
#include "ObjectManagerInterface.h"
#include "Utilities/EnumeratedArray.h"

class StageInterface {
public:
    constexpr static const size_t STAGE_COUNT = 6;

    StageInterface() noexcept = default;
    virtual ~StageInterface() noexcept = default;

    virtual void prepareStage() = 0;
    virtual void setPlayerPosition(Player* player) const = 0;
    virtual void clearStage() = 0;
};



using StageArray = EnumeratedArray<StageChangeEvent::StageID, std::unique_ptr<StageInterface>, StageInterface::STAGE_COUNT>;