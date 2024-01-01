#pragma once


#include "CustomEvents/PostDynamicEventLogger.h"
#include "DeletableObject.h"
#include "Events/Events/LeftClickEvent.h"
#include "Objects/StageSelectButton.h"
class StageSelectSubscriber :
    public Barta::LeftClickEventSubscriberInterface,
    public Barta::DeletableObject {
public:
    explicit StageSelectSubscriber(
        bool* deleteWatch,
        std::vector<StageSelectButton*> stageButtons,
        PostDynamicEventLogger& postDynamicEventLogger
    ) noexcept;
    StageSelectSubscriber(const StageSelectSubscriber&) = delete;
    StageSelectSubscriber& operator=(const StageSelectSubscriber&) = delete;
//    ~StageSelectSubscriber() noexcept;

    bool handle(Barta::LeftClickEvent &event) override;
    bool isValid() const noexcept override;

private:
    std::vector<StageSelectButton*> stageButtons;
    PostDynamicEventLogger& postDynamicEventLogger;
};
