#pragma once
#include "BartaObject.h"
#include "Collisions/CollisionAwareInterface.h"
#include "DeletableObject.h"
#include "SandboxResource.h"
#include <Graphics/BartaSprite.h>
#include <Graphics/Color.h>

class Wall : 
	public Barta::BartaObjectInterface, 
	public Barta::CollisionAwareInterface,
    public Barta::DeletableObject {
public:
    static const Barta::Color WALL_COLOR;

	Wall(
        Barta::Vector2f initialPosition,
        Barta::AABB aabb,
        Barta::BartaSprite resource
    );
	virtual ~Wall() noexcept = default;

    bool isToBeDeleted() const override { return Barta::DeletableObject::isToBeDeleted(); };

	Barta::TransformableInterface& getTransformable() const override;

	const Barta::BartaSprite* getResource() noexcept override;

	std::unique_ptr<const Barta::HitboxInterface> getHitbox() const override;

	void move( const Barta::Vector2f& shift ) override;

	const Barta::DynamicsDTO& getDynamicsDTO() const override;

	void setDynamicsDTO( const Barta::DynamicsDTO& ) override;

	inline void rotate(float, Barta::Vector2f) override {}
    int getZIndex() const override;

protected:
	std::unique_ptr<Barta::TransformableInterface> transformable;
	std::unique_ptr<Barta::HitboxInterface> hitbox;
	Barta::DynamicsDTO dynamicsDTO;

	Barta::BartaSprite resource;
};

