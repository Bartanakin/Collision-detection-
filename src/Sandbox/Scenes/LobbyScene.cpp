//
// Created by barta on 28/12/2023.
//

#include "LobbyScene.h"
#include "Events/Subscribers/HitboxPositionCheckSubscriberProxy.h"
#include "Objects/Button.h"
#include "Stages/StageInterface.h"
#include "Subscribers/ButtonHoverSubscriber.h"
#include "Subscribers/InstructionButtonSubscriber.h"
#include "Subscribers/StageSelectSubscriber.h"
#include "Subscribers/StopGameSubscriber.h"

LobbyScene::LobbyScene(
    Barta::ObjectManagerInterface *objectManager,
    Barta::BartaEventLoggerInterface *eventLogger,
    PostDynamicEventLogger* postDynamicEventLogger,
    bool* isRunning_ptr
) noexcept
    : toBeDeleted(false),
      objectManager(objectManager),
      eventLogger(eventLogger),
      postDynamicEventLogger(postDynamicEventLogger),
      isRunning_ptr(isRunning_ptr),
      bestStageId(StageChangeEvent::StageID::STAGE_I)
{}

void LobbyScene::load() {
    StageArray stages;
    this->toBeDeleted = false;
    std::vector<Button*> buttons;
    auto exitButton = new Button(
        {625.f, 625.f},
        {12.f, 17.f},
        {50.f, 50.f},
        "Exit"
    );
    exitButton->setDeleteWatch(&this->toBeDeleted);
    this->objectManager->addNewObject(exitButton);
    buttons.push_back(exitButton);

    auto instructionButton = new Button(
        {515.f, 625.f},
        {10.f, 17.f},
        {90.f, 50.f},
        "Instruction"
    );
    instructionButton->setDeleteWatch(&this->toBeDeleted);
    this->objectManager->addNewObject(instructionButton);
    buttons.push_back(instructionButton);

    std::vector<StageSelectButton*> stageSelectButtons;
    float pos = 0.f;
    for (const auto& stageId : {
         StageChangeEvent::StageID::STAGE_I,
         StageChangeEvent::StageID::STAGE_II,
         StageChangeEvent::StageID::STAGE_III,
         StageChangeEvent::StageID::STAGE_IV,
         StageChangeEvent::StageID::STAGE_V
    }) {
        auto button = new StageSelectButton(
            {50.f + pos, 100.f},
            {20.f, 15.f},
            {50.f, 50.f},
            std::to_string(static_cast<int>(stageId)),
            stageId
        );
        button->setDeleteWatch(&this->toBeDeleted);
        this->objectManager->addNewObject(button);
        stageSelectButtons.push_back(button);
        buttons.push_back(button);

        if (stageId == this->bestStageId) {
            break;
        }

        pos += 60.f;
    }

    this->eventLogger->logSubscriber(
        std::unique_ptr<Barta::MouseMoveSubscriberInterface>(new ButtonHoverSubscriber(
            &this->toBeDeleted,
            buttons
        ))
    );

    this->eventLogger->logSubscriber(
        std::unique_ptr<Barta::LeftClickEventSubscriberInterface>(new StageSelectSubscriber(
            &this->toBeDeleted,
            stageSelectButtons,
            *this->postDynamicEventLogger
        ))
    );

    this->eventLogger->logSubscriber(
        std::unique_ptr<Barta::LeftClickEventSubscriberInterface>(new Barta::HitboxPositionCheckSubscriberProxy<Barta::LeftClickEvent>(
            exitButton,
            std::unique_ptr<Barta::LeftClickEventSubscriberInterface>(new StopGameSubscriber(
                &this->toBeDeleted,
                this->isRunning_ptr
            ))
        ))
    );

    this->eventLogger->logSubscriber(
        std::unique_ptr<Barta::LeftClickEventSubscriberInterface>(new Barta::HitboxPositionCheckSubscriberProxy<Barta::LeftClickEvent>(
            instructionButton,
            std::unique_ptr<Barta::LeftClickEventSubscriberInterface>(new InstructionButtonSubscriber(
                &this->toBeDeleted,
                *this->postDynamicEventLogger
            ))
        ))
    );
}

void LobbyScene::unload() {
    this->toBeDeleted = true;
    this->eventLogger->removeInvalid();
    this->postDynamicEventLogger->removeInvalid();

    this->objectManager->reduceDeleted();
}
void LobbyScene::setBestStage(StageChangeEvent::StageID stageId) {
    if (stageId > this->bestStageId) {
        this->bestStageId = stageId;
    }
}
