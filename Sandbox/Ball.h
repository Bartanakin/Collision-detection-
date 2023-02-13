#pragma once
#include"BartaObject.h"
#include"Hitbox/HitboxAwareInterface.h"
#include "Dynamics/DynamicsUpdateStrategyInterface.h"

class Ball : public 
	Barta::BartaObjectInterface, 
	Barta::HitboxAware,
	Barta::DynamicsAwareInterface{
public:
	Ball( Barta::Vector2f initialPosition, Barta::DynamicsDTO initialDynamics );
	virtual ~Ball();

	bool isToBeDeleted() const override;

	const Barta::TransformableInterface& getTransformable() override;

	const Barta::Resource getResourceId() const noexcept override;

	const Barta::Resource getBallCollor() const;

	void setBallCollor( Barta::Resource  resource );

	std::unique_ptr<const Barta::HitboxInterface> getHitbox() const override;

	void move( const Barta::Vector2f& shift ) override;

	const Barta::DynamicsDTO& getDynamicsDTO() const override;

	void setDynamicsDTO( const Barta::DynamicsDTO& ) override;

private:
	Barta::TransformableInterface* const transformable;
	Barta::HitboxInterface* const hitbox;
	Barta::DynamicsDTO dynamicsDTO;

	Barta::Resource ballColor;
};

