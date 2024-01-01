#pragma once


#include "BartaObject.h"
#include "DeletableObject.h"
#include "Hitbox/HitboxAwareInterface.h"
#include "Hitbox/HitboxInterface.h"
class Button
    : public Barta::BartaObjectInterface,
      public Barta::DeletableObject,
      public Barta::HitboxAware
{
public:
    Button(
        Barta::Vector2f position,
        Barta::Vector2f testTranslation,
        Barta::Vector2f size,
        std::string string
    );
    ~Button() noexcept override = default;
    bool isToBeDeleted() const override;
    const Barta::TransformableInterface &getTransformable() const override;
    const Barta::BartaSprite *getResource() noexcept override;
    int getZIndex() const override;
    std::unique_ptr<const Barta::HitboxInterface> getHitbox() const override;
    void setIsMouseHover(bool isMouseHover);
private:
    std::unique_ptr<Barta::TransformableInterface> transformable;
    std::unique_ptr<const Barta::HitboxInterface> hitbox;

    bool isMouseHover;
    Barta::BartaSprite resource;
    Barta::BartaSprite hoveredResource;
};
