//
// Created by barta on 01/01/2024.
//

#include "InstructionScene.h"
#include "Events/Subscribers/HitboxPositionCheckSubscriberProxy.h"
#include "Objects/Instruction.h"
#include "Subscribers/ButtonHoverSubscriber.h"
#include "Subscribers/ExitButtonSubscriber.h"
InstructionScene::InstructionScene(
    Barta::ObjectManagerInterface *objectManager,
    Barta::BartaEventLoggerInterface* eventLogger,
    PostDynamicEventLogger *postDynamicEventLogger
) noexcept 
    : objectManager(objectManager),
      eventLogger(eventLogger),
      postDynamicEventLogger(postDynamicEventLogger),
      toBeDeleted(false)
{}


void InstructionScene::load() {
    StageArray stages;
    this->toBeDeleted = false;
    std::vector<Button*> buttons;
    auto exitButton = new Button(
        {625.f, 625.f},
        {7.f, 17.f},
        {50.f, 50.f},
        "Menu"
    );
    exitButton->setDeleteWatch(&this->toBeDeleted);
    this->objectManager->addNewObject(exitButton);
    buttons.push_back(exitButton);

    auto instruction_ptr = new Instruction();
    instruction_ptr->setDeleteWatch(&this->toBeDeleted);
    this->objectManager->addNewObject(instruction_ptr);

    this->eventLogger->logSubscriber(
        std::unique_ptr<Barta::MouseMoveSubscriberInterface>(new ButtonHoverSubscriber(
            &this->toBeDeleted,
            buttons
        ))
    );
    this->eventLogger->logSubscriber(
        std::unique_ptr<Barta::LeftClickEventSubscriberInterface>(new Barta::HitboxPositionCheckSubscriberProxy<Barta::LeftClickEvent>(
            exitButton,
            std::unique_ptr<Barta::LeftClickEventSubscriberInterface>(new ExitButtonSubscriber(
                &this->toBeDeleted,
                *this->postDynamicEventLogger
            ))
        ))
    );
}

void InstructionScene::unload() {
    this->toBeDeleted = true;
    this->eventLogger->removeInvalid();
    this->postDynamicEventLogger->removeInvalid();

    this->objectManager->reduceDeleted();
}