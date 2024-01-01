#include "InstructionButtonSubscriber.h"

InstructionButtonSubscriber::InstructionButtonSubscriber(
    bool* deleteWatch,
    PostDynamicEventLogger &postDynamicEventLogger
    ) noexcept
    : Barta::DeletableObject(deleteWatch),
      postDynamicEventLogger(postDynamicEventLogger)
{}

bool InstructionButtonSubscriber::handle(Barta::LeftClickEvent &event) {
    this->postDynamicEventLogger.logEvent(SceneChangeEvent(SceneChangeEvent::SceneType::INSTRUCTION));

    return true;
}

bool InstructionButtonSubscriber::isValid() const noexcept {
    return !this->isToBeDeleted();
}
