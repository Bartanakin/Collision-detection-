#pragma once
#include "pch.h"

#include "../CustomEvents/StageChangeEvent.h"
#include "../Scenes/GameScene.h"
#include "../Stages/StageInterface.h"
#include "../Scenes/LobbyScene.h"
class StageChangeSubscriber :
    public StageChangeSubscriberInterface,
    public Barta::DeletableObject {
public:
    explicit StageChangeSubscriber(
        StageArray stages,
        GameScene*gameScene_ptr,
        LobbyScene* lobbyScene_ptr
    ) noexcept;
    StageChangeSubscriber(const StageChangeSubscriber&) = delete;
    StageChangeSubscriber& operator=(const StageChangeSubscriber&) = delete;
    ~StageChangeSubscriber() noexcept override;

    bool isValid() const noexcept override;
    bool handle(StageChangeEvent &event) override;
private:
    GameScene* gameScene_ptr;
    StageArray stages;
    LobbyScene* lobbyScene_ptr;
};
