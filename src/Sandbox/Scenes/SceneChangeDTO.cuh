#pragma once

#include "../CustomEvents/StageChangeEvent.h"
#include "../Player.h"
struct SceneChangeDTO {
    StageChangeEvent::StageID stageId;

    Player* player_ptr;
};