#pragma once


#include "../CustomEvents/PostDynamicEventLogger.h"
#include "Events/BartaEventLoggerInterface.h"
#include "ObjectManagerInterface.h"
#include "../Objects/StageSelectButton.h"
#include "SceneInterface.h"
#include "../Stages/StageInterface.h"
class LobbyScene : public SceneInterface {
public:
    LobbyScene(
        Barta::ObjectManagerInterface* objectManager,
        Barta::BartaEventLoggerInterface* eventLogger,
        PostDynamicEventLogger* postDynamicEventLogger,
        bool* isRunning_ptr
    ) noexcept;
    LobbyScene(const LobbyScene&) = delete;
    LobbyScene(LobbyScene&&) = delete;
    LobbyScene& operator=(const LobbyScene&) = delete;
    LobbyScene& operator=(LobbyScene&&) = delete;
//    ~LobbyScene() override;

    void load() override;
    void unload() override;

    void setBestStage(StageChangeEvent::StageID stageId);
private:
    bool toBeDeleted;

    Barta::ObjectManagerInterface* objectManager;
    Barta::BartaEventLoggerInterface* eventLogger;
    PostDynamicEventLogger* postDynamicEventLogger;

    bool* isRunning_ptr;
    StageChangeEvent::StageID bestStageId;
};
