#pragma once
#include"BartaObject.h"
#include "Collisions/CollisionAwareInterface.h"

class Gun: 
    public Barta::BartaObjectInterface,
    public Barta::DynamicsAwareInterface {
	public:

    enum class RotationState {
        STATIONARY,
        CLOCKWISE,
        COUNTER_CLOCKWISE,
    };

	Gun() noexcept;

	bool isToBeDeleted() const override;

	const Barta::TransformableInterface& getTransformable() const override;

	int getResourceId() const noexcept override;

	void move(const Barta::Vector2f& shift) override;

	const Barta::DynamicsDTO& getDynamicsDTO() const override;

	void setDynamicsDTO(const Barta::DynamicsDTO&) override;

	void setVelocity(Barta::Vector2f);

    void setRotationVelocity(float);

    void setPosition(Barta::Vector2f) noexcept;

    RotationState getRotationState() const;

    void setRotationState(RotationState, float);

	void rotate(float, Barta::Vector2f) override;

	float getRotation() const;

	private:
	std::unique_ptr<Barta::TransformableInterface> transformable;
    Barta::DynamicsDTO dynamics;
    RotationState rotationState;
};

