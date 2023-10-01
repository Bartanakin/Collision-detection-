#include "pch.h"
#include "CollisionTestResultBuilder.h"

Barta::CollisionTestResultBuilder::CollisionTestResultBuilder() noexcept :
	collisionDetected(false),
	timePassed(0.f),
	staticCollision(false),
	normVector(0., 0.)
{}

Barta::CollisionTestResult Barta::CollisionTestResultBuilder::build() const noexcept {
	return CollisionTestResult(
		this->collisionDetected,
		this->timePassed,
		this->staticCollision,
		this->normVector
	);
}

void Barta::CollisionTestResultBuilder::reset() noexcept {
	this->collisionDetected = false;
	this->timePassed = 0.f;
	this->staticCollision = false;
	this->normVector = Vector2f(0., 0.);
}

Barta::CollisionTestResultBuilder* Barta::CollisionTestResultBuilder::setCollisionDetected(bool data) noexcept {
	this->collisionDetected = data;

	return this;
}

Barta::CollisionTestResultBuilder* Barta::CollisionTestResultBuilder::setTimePassed(float data) noexcept {
	this->timePassed = data;

	return this;
}

Barta::CollisionTestResultBuilder* Barta::CollisionTestResultBuilder::setStaticCollision(float data) noexcept {
	this->staticCollision = data;
	
	return this;
}

Barta::CollisionTestResultBuilder* Barta::CollisionTestResultBuilder::setNormVector(Barta::Vector2f data) noexcept {
	this->normVector = data;

	return this;
}
