#pragma once
#include"BartaObject.h"
#include "Collisions/CollisionAwareInterface.h"

class Block: public
	Barta::BartaObjectInterface,
	Barta::CollisionAwareInterface {
	public:
	Block(Barta::Vector2f initialPosition, Barta::DynamicsDTO initialDynamics);
	virtual ~Block();

	bool isToBeDeleted() const override;

	const Barta::TransformableInterface& getTransformable() const override;

	const Barta::Resource getResourceId() const noexcept override;

	std::unique_ptr<const Barta::HitboxInterface> getHitbox() const override;

	void move(const Barta::Vector2f& shift) override;

	const Barta::DynamicsDTO& getDynamicsDTO() const override;

	void setDynamicsDTO(const Barta::DynamicsDTO&) override;

	private:
	Barta::TransformableInterface* const transformable;
	Barta::HitboxInterface* const hitbox;
	Barta::DynamicsDTO dynamicsDTO;
};

