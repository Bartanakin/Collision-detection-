#include "StageChangeEvent.h"

StageChangeEvent::StageID& operator++(StageChangeEvent::StageID& stage) {
    auto newStage = static_cast<StageChangeEvent::StageID>(static_cast<int>(stage) + 1);
    if (newStage == StageChangeEvent::StageID::UNDEFINED) {
        stage = StageChangeEvent::StageID::STAGE_I;
    } else {
        stage = newStage;
    }

    return stage;
}
auto operator<=>(
    const StageChangeEvent::StageID &stage1,
    const StageChangeEvent::StageID &stage2
) {
    return static_cast<int>(stage1) <=> static_cast<int>(stage2);
}
