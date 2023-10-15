#pragma once
#include"BartaObject.h"
#include"SandboxResource.h"
#include "Collisions/CollisionAwareInterface.h"

class Ball : 
	public Barta::BartaObjectInterface, 
	public Barta::CollisionAwareInterface {
public:
	Ball( Barta::Vector2f initialPosition, Barta::DynamicsDTO initialDynamics );
	~Ball() noexcept = default;

	bool isToBeDeleted() const override;

	const Barta::TransformableInterface& getTransformable() const override;

	int getResourceId() const noexcept override;

	SandboxResource getBallCollor() const;

	void setBallCollor( SandboxResource  resource );

	std::unique_ptr<const Barta::HitboxInterface> getHitbox() const override;

	void move( const Barta::Vector2f& shift ) override;

	const Barta::DynamicsDTO& getDynamicsDTO() const override;

	void setDynamicsDTO( const Barta::DynamicsDTO& ) override;

	inline virtual void rotate(float, Barta::Vector2f) override {}

private:
	std::unique_ptr<Barta::TransformableInterface> transformable;
	std::unique_ptr<Barta::HitboxInterface> hitbox;
	Barta::DynamicsDTO dynamicsDTO;

	SandboxResource ballColor;
};

