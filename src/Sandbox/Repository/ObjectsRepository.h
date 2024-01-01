#pragma once


#include "../ListsDefinitions.h"
#include "ObjectManagerInterface.h"
class ObjectsRepository {
public:
    explicit ObjectsRepository(
        ListManager& listManager,
        Barta::ObjectManagerInterface& objectManager
    ) noexcept;
    void addWalls();
private:
    ListManager& listManager;
    Barta::ObjectManagerInterface& objectManager;
};
