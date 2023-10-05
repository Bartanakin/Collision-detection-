#pragma once
#include"BartaObject.h"
#include "Collisions/CollisionAwareInterface.h"

class Ball : 
	public Barta::BartaObjectInterface, 
	public Barta::CollisionAwareInterface {
public:
	Ball( Barta::Vector2f initialPosition, Barta::DynamicsDTO initialDynamics );
	~Ball() noexcept = default;

	bool isToBeDeleted() const override;

	const Barta::TransformableInterface& getTransformable() const override;

	Barta::Resource getResourceId() const noexcept override;

	Barta::Resource getBallCollor() const;

	void setBallCollor( Barta::Resource  resource );

	std::unique_ptr<const Barta::HitboxInterface> getHitbox() const override;

	void move( const Barta::Vector2f& shift ) override;

	const Barta::DynamicsDTO& getDynamicsDTO() const override;

	void setDynamicsDTO( const Barta::DynamicsDTO& ) override;

private:
	std::unique_ptr<Barta::TransformableInterface> transformable;
	std::unique_ptr<Barta::HitboxInterface> hitbox;
	Barta::DynamicsDTO dynamicsDTO;

	Barta::Resource ballColor;
};

