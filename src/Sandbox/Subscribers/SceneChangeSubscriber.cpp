//
// Created by barta on 25/12/2023.
//

#include "SceneChangeSubscriber.h"
SceneChangeSubscriber::SceneChangeSubscriber(
    SceneArray scenes,
    SceneChangeEvent::SceneType& currentScene
) noexcept
    : currentScene(currentScene),
      scenes(std::move(scenes)) {
    this->scenes[this->currentScene]->load();
}

bool SceneChangeSubscriber::isValid() const noexcept {
    return true;
}

bool SceneChangeSubscriber::handle(SceneChangeEvent &event) {
    this->scenes[this->currentScene]->unload();

    this->currentScene = event.sceneType;

    this->scenes[this->currentScene]->load();

    return true;
}
