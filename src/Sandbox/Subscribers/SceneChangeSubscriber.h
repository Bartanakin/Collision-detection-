#pragma once
#include "pch.h"


#include "../CustomEvents/SceneChangeEvent.h"
#include "../Scenes/SceneInterface.h"
class SceneChangeSubscriber : public SceneChangeSubscriberInterface {
public:
    SceneChangeSubscriber(
        SceneArray scenes,
        SceneChangeEvent::SceneType& currentScene
    ) noexcept;
    SceneChangeSubscriber(const SceneChangeSubscriber&) = delete;
    SceneChangeSubscriber& operator=(const SceneChangeSubscriber&) = delete;
    virtual ~SceneChangeSubscriber() noexcept = default;

    bool isValid() const noexcept override;
    bool handle(SceneChangeEvent &event) override;
private:
    SceneChangeEvent::SceneType& currentScene;

    SceneArray scenes;
};
