#pragma once

#include <Events/TemplateEventSubscriber.h>

class StageChangeEvent {
public:
    enum class StageID {
        NO_STAGE = 0,
        STAGE_I = 1,
        STAGE_II = 2,
        STAGE_III = 3,
        STAGE_IV = 4,
        STAGE_V = 5,
        UNDEFINED = 6
    };

    explicit StageChangeEvent(
        StageID stageId
    ) noexcept:
          stageId(stageId)
    {}
    StageChangeEvent(const StageChangeEvent&) = delete;
    StageChangeEvent(StageChangeEvent&&) noexcept = default;
    StageChangeEvent& operator=(const StageChangeEvent&) = delete;
    ~StageChangeEvent() noexcept = default;

    StageID stageId;
};

StageChangeEvent::StageID& operator++(StageChangeEvent::StageID& stage);
auto operator<=>(const StageChangeEvent::StageID& stage1, const StageChangeEvent::StageID& stage2);

SUBSCRIBER_INTERFACE_DEFINITION(StageChangeEvent);

using StageChangeSubscriberInterface = Barta::EventSubscriber<StageChangeEvent>;
