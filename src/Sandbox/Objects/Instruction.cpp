//
// Created by barta on 01/01/2024.
//

#include "Instruction.h"
#include "BartaGraph.h"
Instruction::Instruction() noexcept
    : transformable(std::move(BartaGraph::createNewTransformableInstance())),
      resource(Barta::BartaSprite(static_cast<int>(SandboxResource::INSTRUCTION)))
{
    this->transformable->setPosition({100.f, 100.f});
}


bool Instruction::isToBeDeleted() const {
    return Barta::DeletableObject::isToBeDeleted();
}

const Barta::TransformableInterface &Instruction::getTransformable() const {
    return *this->transformable;
}

const Barta::BartaSprite *Instruction::getResource() noexcept {
    return &this->resource;
}

int Instruction::getZIndex() const {
    return 6;
}