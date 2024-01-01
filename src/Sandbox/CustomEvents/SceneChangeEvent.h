#pragma once

#include <Events/TemplateEventSubscriber.h>

class SceneChangeEvent {
public:
    enum class SceneType {
        GAME = 0,
        LOBBY = 1,
        INSTRUCTION = 2,
        UNDEFINED = 3
    };

    explicit SceneChangeEvent(
        SceneType sceneType
    ) noexcept:
        sceneType(sceneType)
    {}
    SceneChangeEvent(const SceneChangeEvent&) = delete;
    SceneChangeEvent(SceneChangeEvent&&) noexcept = default;
    SceneChangeEvent& operator=(const SceneChangeEvent&) = delete;
    ~SceneChangeEvent() noexcept = default;

    SceneType sceneType;
};

SUBSCRIBER_INTERFACE_DEFINITION(SceneChangeEvent);

using SceneChangeSubscriberInterface = Barta::EventSubscriber<SceneChangeEvent>;
