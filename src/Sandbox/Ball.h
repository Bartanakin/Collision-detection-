#pragma once
#include"BartaObject.h"
#include"SandboxResource.h"
#include "Collisions/CollisionAwareInterface.h"
#include <Graphics/SpriteBuilder/SpriteMerger.h>

class Ball : 
	public Barta::BartaObjectInterface, 
	public Barta::CollisionAwareInterface {
public:
    enum class BallSize {
        VERY_SMALL = 0,
        SMALL = 1,
        MEDIUM = 2,
        LARGE = 3
    };
    const static std::array<float, 4> ballSizes;

	Ball(
        Barta::Vector2f initialPosition,
        Barta::DynamicsDTO initialDynamics,
        BallSize size
    );
	~Ball() noexcept = default;

	bool isToBeDeleted() const override;

	const Barta::TransformableInterface& getTransformable() const override;

	const Barta::BartaSprite* getResource() noexcept override;

	std::unique_ptr<const Barta::HitboxInterface> getHitbox() const override;

	void move( const Barta::Vector2f& shift ) override;

	const Barta::DynamicsDTO& getDynamicsDTO() const override;

	void setDynamicsDTO( const Barta::DynamicsDTO& ) override;

	inline virtual void rotate(float, Barta::Vector2f) override {}

private:
	std::unique_ptr<Barta::TransformableInterface> transformable;
	std::unique_ptr<Barta::HitboxInterface> hitbox;
	Barta::DynamicsDTO dynamicsDTO;

	Barta::BartaSprite resource;
};

