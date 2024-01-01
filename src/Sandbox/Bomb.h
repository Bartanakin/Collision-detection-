#pragma once
#include"BartaObject.h"
#include "Collisions/CollisionAwareInterface.h"
#include "Gun.h"
#include "DeletableObject.h"

class Bomb: 
    public Barta::BartaObjectInterface,
	public Barta::CollisionAwareInterface,
    public Barta::DeletableObject {
	public:

	Bomb(
        Barta::Vector2f initPosition,
        Barta::DynamicsDTO initDynamics
    ) noexcept;
	~Bomb() noexcept = default;

    bool isToBeDeleted() const override { return Barta::DeletableObject::isToBeDeleted(); };

	const Barta::TransformableInterface& getTransformable() const override;

	const Barta::BartaSprite* getResource() noexcept override;

	std::unique_ptr<const Barta::HitboxInterface> getHitbox() const override;

	void move(const Barta::Vector2f& shift) override;
	
    void rotate(float, Barta::Vector2f) override {};

	const Barta::DynamicsDTO& getDynamicsDTO() const override;

	void setDynamicsDTO(const Barta::DynamicsDTO&) override;

    void markToBeDeleted();
    int getZIndex() const override;

private:
	std::unique_ptr<Barta::TransformableInterface> transformable;
	std::unique_ptr<Barta::HitboxInterface> hitbox;

    Barta::DynamicsDTO dynamics;

	Barta::BartaSprite resource;
};

