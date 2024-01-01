#pragma once


#include "ListsDefinitions.h"
#include "Player.h"
#include "../Repository/ObjectsRepository.h"
#include "StageInterface.h"
class StageTwo : public StageInterface {
public:
    StageTwo(
        ListManager& listManager,
        Barta::ObjectManagerInterface& objectManager,
        ObjectsRepository objectsRepository
    ) noexcept;
    StageTwo(const StageTwo&) = delete;
    StageTwo(StageTwo&&) = default;
    StageTwo& operator=(const StageTwo&) = delete;
    StageTwo& operator=(StageTwo&&) = default;

    void prepareStage() override;
    void setPlayerPosition(Player *player) const override;
    void clearStage() override;
private:
    bool deleteWatch;

    ListManager& listManager;
    Barta::ObjectManagerInterface& objectManager;
    ObjectsRepository objectsRepository;
};
