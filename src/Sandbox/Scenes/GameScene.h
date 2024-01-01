#pragma once


#include "BartaObjectManager.h"
#include "../CustomEvents/PostDynamicEventLogger.h"
#include "Events/BartaEventLoggerInterface.h"
#include "../ListsDefinitions.h"
#include "../Player.h"
#include "SceneInterface.h"

class GameScene : public SceneInterface{
public:
    GameScene(
        Barta::ObjectManagerInterface* objectManager,
        Barta::BartaEventLoggerInterface* eventLogger,
        Barta::BartaEventLoggerInterface* postDynamicsEventLogger,
        ListManager& objectLists,
        CollisionEventsLogger& collisionEventsLogger,
        PostDynamicEventLogger* postDynamicEventLogger,
        StageChangeEvent::StageID&selectedStage
    ) noexcept;
    GameScene(const GameScene&) = delete;
    GameScene(GameScene&&) = delete;
    GameScene& operator=(const GameScene&) = delete;
    GameScene& operator=(GameScene&&) = delete;
    ~GameScene() override;

    void load() override;
    void unload() override;

    StageChangeEvent::StageID getCurrentStageId() const;
    void setCurrentStageId(StageChangeEvent::StageID);
    Player* getPlayer();

private:
    bool toBeDeleted;

    Barta::ObjectManagerInterface* objectManager;
    Barta::BartaEventLoggerInterface* eventLogger;
    Barta::BartaEventLoggerInterface* postDynamicsEventLogger;
    ListManager& objectLists;
    CollisionEventsLogger& collisionEventsLogger;
    PostDynamicEventLogger* postDynamicEventLogger;

    StageChangeEvent::StageID& selectedStage;
    Player* player_ptr;
};
