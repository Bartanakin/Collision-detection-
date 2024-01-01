#pragma once


#include "ListsDefinitions.h"
#include "Player.h"
#include "../Repository/ObjectsRepository.h"
#include "StageInterface.h"
class StageFive : public StageInterface {
public:
    StageFive(
        ListManager& listManager,
        Barta::ObjectManagerInterface& objectManager,
        ObjectsRepository objectsRepository
        ) noexcept;
    StageFive(const StageFive&) = delete;
    StageFive(StageFive&&) = default;
    StageFive& operator=(const StageFive&) = delete;
    StageFive& operator=(StageFive&&) = default;

    void prepareStage() override;
    void setPlayerPosition(Player *player) const override;
    void clearStage() override;
private:
    bool deleteWatch;

    ListManager& listManager;
    Barta::ObjectManagerInterface& objectManager;
    ObjectsRepository objectsRepository;
};
