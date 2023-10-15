#include "Gun.h"
#include "BartaGraph.h"
#include "SandboxResource.h"

Gun::Gun() noexcept : 
	transformable(std::move(BartaGraph::createNewTransformableInstance())),
    dynamics({Barta::Vector2f(), false}),
    rotationState(RotationState::STATIONARY)
{
    this->dynamics.massCenter = {10.f, 20.f};
}

bool Gun::isToBeDeleted() const{
	return false;
}

const Barta::TransformableInterface& Gun::getTransformable() const{
	return *this->transformable;
}

int Gun::getResourceId() const noexcept{
	return static_cast<int>(SandboxResource::GREEN_ARROW);
}

void Gun::move(const Barta::Vector2f& shift){
	this->transformable->move( shift );
}

const Barta::DynamicsDTO& Gun::getDynamicsDTO() const{
	return this->dynamics;
}

void Gun::setDynamicsDTO(const Barta::DynamicsDTO& dynamics){
    this->dynamics = dynamics;
}

void Gun::setVelocity(Barta::Vector2f velocity) {
    this->dynamics.velocity = velocity;
}

void Gun::setRotationVelocity(float rotationVelocity) {
    this->dynamics.rotationVelocity = rotationVelocity;
}

void Gun::setPosition(Barta::Vector2f position) noexcept {
    this->transformable->setPosition(position);
}

Gun::RotationState Gun::getRotationState() const {
    return this->rotationState;
}

void Gun::setRotationState(RotationState rotationState, float rotationVelocity) {
    this->dynamics.rotationVelocity = rotationVelocity;
    this->rotationState = rotationState;
}

void Gun::rotate(float angle, Barta::Vector2f axis) {
    this->transformable->rotate(angle, axis);
}

float Gun::getRotation() const {
    return this->transformable->getRotaion();
}
