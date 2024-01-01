#pragma once
#include "BartaObject.h"
#include "Collisions/CollisionAwareInterface.h"
#include "DeletableObject.h"
#include "SandboxResource.h"
#include <Graphics/SpriteBuilder/SpriteMerger.h>
#include <functional>

class Ball : 
	public Barta::BartaObjectInterface, 
	public Barta::CollisionAwareInterface,
    public Barta::DeletableObject {
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
        BallSize size
    );
	~Ball() noexcept = default;

    bool isToBeDeleted() const override { return Barta::DeletableObject::isToBeDeleted(); };

	const Barta::TransformableInterface& getTransformable() const override;

	const Barta::BartaSprite* getResource() noexcept override;

	std::unique_ptr<const Barta::HitboxInterface> getHitbox() const override;

	void move( const Barta::Vector2f& shift ) override;

	const Barta::DynamicsDTO& getDynamicsDTO() const override;

	void setDynamicsDTO( const Barta::DynamicsDTO& ) override;

	inline virtual void rotate(float, Barta::Vector2f) override {}

	float getRebounceVelocity() const;

    BallSize getSize() const;

    inline void setVelocity(Barta::Vector2f velocity) { this->dynamicsDTO.velocity = velocity; }

    int getZIndex() const override;

private:
	std::unique_ptr<Barta::TransformableInterface> transformable;
	std::unique_ptr<Barta::HitboxInterface> hitbox;
	Barta::DynamicsDTO dynamicsDTO;
    BallSize size;

	Barta::BartaSprite resource;
};

Ball::BallSize& operator--(Ball::BallSize& ballSize);