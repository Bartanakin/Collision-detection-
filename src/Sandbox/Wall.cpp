#include "Wall.h"
#include "Hitbox/AABB_Hitbox.h"
#include "BartaGraph.h"
#include "SandboxResource.h"

constexpr const Barta::Color Wall::WALL_COLOR = Barta::Color(87, 150, 138);

Wall::Wall(
    Barta::Vector2f initialPosition,
    Barta::AABB aabb,
    Barta::BartaSprite resource
) :
    transformable(std::move(BartaGraph::createNewTransformableInstance())),
	hitbox(new Barta::AABB_Hitbox(aabb)),
	dynamicsDTO(Barta::DynamicsDTO({0.f, 0.f})),
    resource(std::move(resource))
{
	this->transformable->setPosition(initialPosition);
}

Barta::TransformableInterface& Wall::getTransformable() const {
	return *this->transformable;
}

const Barta::BartaSprite* Wall::getResource() noexcept {
	return &this->resource;
}

std::unique_ptr<const Barta::HitboxInterface> Wall::getHitbox() const {
	return this->hitbox->getTransformedHitbox(*this->transformable);
}

void Wall::move(const Barta::Vector2f& shift) {
	this->transformable->move(shift);
}

const Barta::DynamicsDTO& Wall::getDynamicsDTO() const {
	return this->dynamicsDTO;
}

void Wall::setDynamicsDTO(const Barta::DynamicsDTO& dynamicsDTO) {
	this->dynamicsDTO = dynamicsDTO;
}
int Wall::getZIndex() const {
    return 0;
}
