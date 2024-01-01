#pragma once

#include "../ListsDefinitions.h"
#include "../Repository/ObjectsRepository.h"
#include "StageInterface.h"

class StageOne : public StageInterface {
public:
    StageOne(
        ListManager& listManager,
        Barta::ObjectManagerInterface& objectManager,
        ObjectsRepository objectsRepository
    ) noexcept;
    StageOne(const StageOne&) = delete;
    StageOne(StageOne&&) = default;
    StageOne& operator=(const StageOne&) = delete;
    StageOne& operator=(StageOne&&) = default;

    void prepareStage() override;
    void setPlayerPosition(Player *player) const override;
    void clearStage() override;
private:
    bool deleteWatch;

    ListManager& listManager;
    Barta::ObjectManagerInterface& objectManager;
    ObjectsRepository objectsRepository;
};
