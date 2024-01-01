#pragma once


#include "BartaObject.h"
#include "DeletableObject.h"
class Instruction
    : public Barta::BartaObjectInterface,
      public Barta::DeletableObject {
public:
    Instruction() noexcept;
    ~Instruction() noexcept override = default;
    bool isToBeDeleted() const override;
    const Barta::TransformableInterface &getTransformable() const override;
    const Barta::BartaSprite *getResource() noexcept override;
    int getZIndex() const override;
private:
    std::unique_ptr<Barta::TransformableInterface> transformable;
    Barta::BartaSprite resource;
};
