#include "Bomb.h"
#include "SandboxResource.h"
#include "BartaGraph.h"
#include <Hitbox/CircleHitbox.h>

Bomb::Bomb(
    Barta::Vector2f initPosition,
    Barta::DynamicsDTO initDynamics
) noexcept :
    transformable(std::move(BartaGraph::createNewTransformableInstance())),
    hitbox(new Barta::CircleHitbox(Barta::Circle(10.f, Barta::Vector2f(10.f, 10.f)))),
    dynamics(initDynamics),
    toDelete(false),
    resource(std::move(Barta::BartaSprite(static_cast<int>(SandboxResource::BOMB))))
{
    this->transformable->setPosition(initPosition);
}

bool Bomb::isToBeDeleted() const {
    return this->toDelete;
}

const Barta::TransformableInterface &Bomb::getTransformable() const {
    return *this->transformable;
}

const Barta::BartaSprite* Bomb::getResource() noexcept {
	return &this->resource;
}

std::unique_ptr<const Barta::HitboxInterface> Bomb::getHitbox() const {
	return std::unique_ptr<const Barta::HitboxInterface>(this->hitbox->getTransformedHitbox(*this->transformable));
}

void Bomb::move(const Barta::Vector2f &shift) {
    this->transformable->move(shift);
}

const Barta::DynamicsDTO &Bomb::getDynamicsDTO() const {
    return this->dynamics;
}

void Bomb::setDynamicsDTO(const Barta::DynamicsDTO& dynamics) {
    this->dynamics = dynamics;
}
