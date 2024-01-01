#pragma once


#include "ListsDefinitions.h"
#include "Player.h"
#include "../Repository/ObjectsRepository.h"
#include "StageInterface.h"
class StageThree : public StageInterface {
public:
    StageThree(
        ListManager& listManager,
        Barta::ObjectManagerInterface& objectManager,
        ObjectsRepository objectsRepository
        ) noexcept;
    StageThree(const StageThree&) = delete;
    StageThree(StageThree&&) = default;
    StageThree& operator=(const StageThree&) = delete;
    StageThree& operator=(StageThree&&) = default;

    void prepareStage() override;
    void setPlayerPosition(Player *player) const override;
    void clearStage() override;
private:
    bool deleteWatch;

    ListManager& listManager;
    Barta::ObjectManagerInterface& objectManager;
    ObjectsRepository objectsRepository;
};
