#pragma once
#include"BartaObject.h"
#include "Collisions/CollisionAwareInterface.h"
#include "Gun.h"

class Bomb: 
    public Barta::BartaObjectInterface,
	public Barta::CollisionAwareInterface {
	public:

	Bomb(
        Barta::Vector2f initPosition,
        Barta::DynamicsDTO initDynamics
    ) noexcept;
	~Bomb() noexcept = default;

	bool isToBeDeleted() const override;

	const Barta::TransformableInterface& getTransformable() const override;

	int getResourceId() const noexcept override;

	std::unique_ptr<const Barta::HitboxInterface> getHitbox() const override;

	void move(const Barta::Vector2f& shift) override;
	
    void rotate(float, Barta::Vector2f) override {};

	const Barta::DynamicsDTO& getDynamicsDTO() const override;

	void setDynamicsDTO(const Barta::DynamicsDTO&) override;

    void markToBeDeleted() { this->toDelete = true; }

	private:
	std::unique_ptr<Barta::TransformableInterface> transformable;
	std::unique_ptr<Barta::HitboxInterface> hitbox;

    Barta::DynamicsDTO dynamics;
    bool toDelete;
};

