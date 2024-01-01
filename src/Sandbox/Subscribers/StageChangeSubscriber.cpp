//
// Created by barta on 25/12/2023.
//

#include "StageChangeSubscriber.h"
StageChangeSubscriber::StageChangeSubscriber(
    StageArray stages,
    GameScene* gameScene_ptr,
    LobbyScene* lobbyScene_ptr
) noexcept
    : gameScene_ptr(gameScene_ptr),
      stages(std::move(stages)),
      lobbyScene_ptr(lobbyScene_ptr)
{
    this->stages[this->gameScene_ptr->getCurrentStageId()]->prepareStage();
}

bool StageChangeSubscriber::isValid() const noexcept {
    return true;
}

bool StageChangeSubscriber::handle(StageChangeEvent &event) {
    this->stages[this->gameScene_ptr->getCurrentStageId()]->clearStage();

    this->gameScene_ptr->setCurrentStageId(event.stageId);

    this->stages[this->gameScene_ptr->getCurrentStageId()]->prepareStage();
    this->stages[this->gameScene_ptr->getCurrentStageId()]->setPlayerPosition(this->gameScene_ptr->getPlayer());

    this->lobbyScene_ptr->setBestStage(event.stageId);

    return true;
}

StageChangeSubscriber::~StageChangeSubscriber() noexcept {
    this->stages[this->gameScene_ptr->getCurrentStageId()]->clearStage();
}