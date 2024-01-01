#pragma once


#include "../CustomEvents/PostDynamicEventLogger.h"
#include "Events/BartaEventLoggerInterface.h"
#include "ObjectManagerInterface.h"
#include "../Objects/StageSelectButton.h"
#include "SceneInterface.h"
#include "../Stages/StageInterface.h"
class InstructionScene : public SceneInterface {
public:
    InstructionScene(
        Barta::ObjectManagerInterface* objectManager,
        Barta::BartaEventLoggerInterface* eventLogger,
        PostDynamicEventLogger* postDynamicEventLogger
    ) noexcept;
    InstructionScene(const InstructionScene &) = delete;
    InstructionScene(InstructionScene &&) = delete;
    InstructionScene & operator=(const InstructionScene &) = delete;
    InstructionScene & operator=(InstructionScene &&) = delete;
    //    ~InstructionScene() override;

    void load() override;
    void unload() override;
private:
    Barta::ObjectManagerInterface* objectManager;
    Barta::BartaEventLoggerInterface* eventLogger;
    PostDynamicEventLogger* postDynamicEventLogger;

    bool toBeDeleted;
};
