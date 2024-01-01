#pragma once


#include "BartaObject.h"
#include "DeletableObject.h"
class Flash
    : public Barta::BartaObjectInterface,
      public Barta::DeletableObject {
public:
    Flash(
        Barta::Vector2f position
    );
    ~Flash() noexcept override = default;
    bool isToBeDeleted() const override;
    const Barta::TransformableInterface &getTransformable() const override;
    const Barta::BartaSprite *getResource() noexcept override;
    int getZIndex() const override;
    void setMessage(std::string message, std::chrono::seconds seconds);
private:
    Barta::BartaSprite createResource(std::string message);

    std::unique_ptr<Barta::TransformableInterface> transformable;
    Barta::BartaSprite resource;

    std::chrono::time_point<std::chrono::steady_clock> until;
    Barta::BartaSprite emptyResource;
};
