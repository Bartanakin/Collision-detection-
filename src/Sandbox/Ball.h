#pragma once
#include"BartaObject.h"
#include"SandboxResource.h"
#include "Collisions/CollisionAwareInterface.h"
#include <Graphics/SpriteBuilder/SpriteMerger.h>
#include <functional>

class Ball : 
	public Barta::BartaObjectInterface, 
	public Barta::CollisionAwareInterface {
public:
    enum class BallSize {
        VERY_SMALL = 1,
        SMALL = 2,
        MEDIUM = 3,
        LARGE = 4
    };

    const static std::function<float(BallSize)> ballSize;
    const static std::function<float(BallSize)> velocity;
    const static std::function<float(BallSize)> mass;
    const static float horizontalSpeed;

	Ball(
        Barta::Vector2f initialPosition,
        bool movingLeft,
        BallSize size,
        Barta::Vector2f gravity
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

	float getRebounceVelocity() const;

    BallSize getSize() const;

    inline void markToBeDeleted() { this->toBeDeleted = true; }

    inline void setVelocity(Barta::Vector2f velocity) { this->dynamicsDTO.velocity = velocity; }

private:
	std::unique_ptr<Barta::TransformableInterface> transformable;
	std::unique_ptr<Barta::HitboxInterface> hitbox;
	Barta::DynamicsDTO dynamicsDTO;
    BallSize size;

	Barta::BartaSprite resource;
    bool toBeDeleted;
};

Ball::BallSize& operator--(Ball::BallSize& ballSize);