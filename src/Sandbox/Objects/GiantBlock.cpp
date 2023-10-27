#include "GiantBlock.h"
#include "Hitbox/AABB_Hitbox.h"
#include "../BartaGraph.h"
#include "../SandboxResource.h"

GiantBlock::GiantBlock(Barta::Vector2f initialPosition) 
	:transformable(std::move(BartaGraph::createNewTransformableInstance())),
	hitbox(new Barta::AABB_Hitbox(Barta::AABB(Barta::Vector2f(0.f, 0.f), Barta::Vector2f(500.f, 500.f)))),
	dynamicsDTO(Barta::DynamicsDTO({0.f, 0.f})),
    resource(std::move(Barta::BartaSprite(static_cast<int>(SandboxResource::GIANT_BLOCK))))
{
	this->transformable->setPosition(initialPosition);
}

bool GiantBlock::isToBeDeleted() const {
	return false;
}

Barta::TransformableInterface& GiantBlock::getTransformable() const {
	return *this->transformable;
}

const Barta::BartaSprite* GiantBlock::getResource() noexcept {
	return &this->resource;
}

std::unique_ptr<const Barta::HitboxInterface> GiantBlock::getHitbox() const {
	return this->hitbox->getTransformedHitbox(*this->transformable);
}

void GiantBlock::move(const Barta::Vector2f& shift) {
	this->transformable->move(shift);
}

const Barta::DynamicsDTO& GiantBlock::getDynamicsDTO() const {
	return this->dynamicsDTO;
}

void GiantBlock::setDynamicsDTO(const Barta::DynamicsDTO&) {
	this->dynamicsDTO = dynamicsDTO;
}
