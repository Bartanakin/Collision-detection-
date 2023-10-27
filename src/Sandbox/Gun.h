#pragma once
#include"BartaObject.h"
#include "Collisions/CollisionAwareInterface.h"

using namespace std::literals;

class Gun: 
    public Barta::BartaObjectInterface,
    public Barta::DynamicsAwareInterface {
	public:

    enum class RotationState {
        STATIONARY,
        CLOCKWISE,
        COUNTER_CLOCKWISE,
    };

    static const std::chrono::milliseconds reloadTime;

	Gun() noexcept;

	bool isToBeDeleted() const override;

	const Barta::TransformableInterface& getTransformable() const override;

	const Barta::BartaSprite* getResource() noexcept override;

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

    std::chrono::milliseconds getLeftToReload() const;

    void setLastShotTime(std::chrono::steady_clock::time_point shotTime);

	private:
	std::unique_ptr<Barta::TransformableInterface> transformable;
    Barta::DynamicsDTO dynamics;
    RotationState rotationState;

    std::chrono::steady_clock::time_point lastShotTime;
    Barta::BartaSprite resource;
};

