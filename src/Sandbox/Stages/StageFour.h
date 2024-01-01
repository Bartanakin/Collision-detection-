#pragma once


#include "ListsDefinitions.h"
#include "Player.h"
#include "../Repository/ObjectsRepository.h"
#include "StageInterface.h"
class StageFour : public StageInterface {
public:
    StageFour(
        ListManager& listManager,
        Barta::ObjectManagerInterface& objectManager,
        ObjectsRepository objectsRepository
        ) noexcept;
    StageFour(const StageFour&) = delete;
    StageFour(StageFour&&) = default;
    StageFour& operator=(const StageFour&) = delete;
    StageFour& operator=(StageFour&&) = default;

    void prepareStage() override;
    void setPlayerPosition(Player *player) const override;
    void clearStage() override;
private:
    bool deleteWatch;

    ListManager& listManager;
    Barta::ObjectManagerInterface& objectManager;
    ObjectsRepository objectsRepository;
};
