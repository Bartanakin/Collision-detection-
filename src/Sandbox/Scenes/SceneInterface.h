#pragma once


#include "Utilities/EnumeratedArray.h"
#include "../CustomEvents/SceneChangeEvent.h"
class SceneInterface {
public:
    SceneInterface() noexcept = default;
    virtual ~SceneInterface() = default;
    virtual void load() = 0;
    virtual void unload() = 0;
};

using SceneArray = EnumeratedArray<SceneChangeEvent::SceneType, std::unique_ptr<SceneInterface>, 3>;