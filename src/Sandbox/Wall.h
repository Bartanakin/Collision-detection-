#pragma once
#include"BartaObject.h"
#include"SandboxResource.h"
#include "Collisions/CollisionAwareInterface.h"
#include <Graphics/BartaSprite.h>

class Wall : 
	public Barta::BartaObjectInterface, 
	public Barta::CollisionAwareInterface {
public:
	Wall(
        Barta::Vector2f initialPosition,
        Barta::AABB aabb,
        Barta::BartaSprite resource
    );
	~Wall() noexcept = default;

	bool isToBeDeleted() const override;

	Barta::TransformableInterface& getTransformable() const override;

	const Barta::BartaSprite* getResource() noexcept override;

	std::unique_ptr<const Barta::HitboxInterface> getHitbox() const override;

	void move( const Barta::Vector2f& shift ) override;

	const Barta::DynamicsDTO& getDynamicsDTO() const override;

	void setDynamicsDTO( const Barta::DynamicsDTO& ) override;

	inline virtual void rotate(float, Barta::Vector2f) override {}

protected:
	std::unique_ptr<Barta::TransformableInterface> transformable;
	std::unique_ptr<Barta::HitboxInterface> hitbox;
	Barta::DynamicsDTO dynamicsDTO;

	Barta::BartaSprite resource;
};

