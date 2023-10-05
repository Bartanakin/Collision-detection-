#include "pch.h"
#include "CollisionResponseSubscriber.h"

Barta::CollisionResponseSubscriber::CollisionResponseSubscriber(BartaEventLoggerInterface& eventLogger)
	: eventLogger(eventLogger) {

}

bool Barta::CollisionResponseSubscriber::handle(CollisionEvent& event) {
	auto& [testResult, firstObject, secondObject] = event.getTestResult();
	if (testResult.staticCollision) {
		return true;
	}

	const auto& firstDynamics = firstObject->getDynamicsDTO();
	const auto& secondDynamics = secondObject->getDynamicsDTO();

	float massInverted = 0.f;
	if (!firstDynamics.hasInfiniteMass) {
		massInverted += 1.f / firstDynamics.mass;
	}

	if (!secondDynamics.hasInfiniteMass) {
		massInverted += 1.f / secondDynamics.mass;
	}

	if (massInverted == 0.f) {
		return true;
	}

	auto j = -(1.f + this->COEFFICIENT_OF_ELISTICITY) * ((secondDynamics.velocity - firstDynamics.velocity) * testResult.normVector) / (testResult.normVector * testResult.normVector * massInverted);
	this->calculateNewVelocity(-j, firstObject, testResult.normVector);
	this->calculateNewVelocity(j, secondObject, testResult.normVector);

	return true;
}

bool Barta::CollisionResponseSubscriber::isValid() const noexcept {
	return true;
}

void Barta::CollisionResponseSubscriber::calculateNewVelocity(
	float j,
	CollisionAwareInterface* dynamicsObject,
	Vector2f normVector
) const noexcept {
	const auto& oldDynamics = dynamicsObject->getDynamicsDTO();
	if (oldDynamics.hasInfiniteMass) {
		return;
	}

	this->eventLogger.logEvent(std::unique_ptr<DynamicsChangeEvent>(new DynamicsChangeEvent(
		static_cast<DynamicsAwareInterface*>(dynamicsObject),
		DynamicsDTO(normVector * (j / oldDynamics.mass), oldDynamics.hasInfiniteMass, oldDynamics.mass)
	)));
}