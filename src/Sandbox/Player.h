#pragma once
#include"BartaObject.h"
#include "Collisions/CollisionAwareInterface.h"
#include "Gun.h"

class Player: 
    public Barta::BartaObjectInterface,
	public Barta::CollisionAwareInterface {
	public:

    enum class Position {
        LOOSE,
        LEFT_WALL,
        RIGHT_WALL,
    };

	Player(
        Barta::Vector2f initialPosition,
        Barta::DynamicsDTO dynamics,
        Gun* gun
    );
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
	~Player() noexcept = default;

	bool isToBeDeleted() const override;

	const Barta::TransformableInterface& getTransformable() const override;

	const Barta::BartaSprite* getResource() noexcept override;

	std::unique_ptr<const Barta::HitboxInterface> getHitbox() const override;

	void move(const Barta::Vector2f& shift) override;

	const Barta::DynamicsDTO& getDynamicsDTO() const override;

	void setDynamicsDTO(const Barta::DynamicsDTO&) override;

	void setVelocity(Barta::Vector2f);

    inline Position getScenePosition() const noexcept { return this->position; }

    inline void setScenePosition(Position position) noexcept { this->position = position; }

	inline virtual void rotate(float, Barta::Vector2f) override {}

    inline Gun* getGun() const { return this->gun; }

	private:
	std::unique_ptr<Barta::TransformableInterface> transformable;
	std::unique_ptr<Barta::HitboxInterface> hitbox;

    Barta::DynamicsDTO dynamics;
    Position position = Position::LOOSE;
    Gun* gun;

    Barta::BartaSprite resource;
};

