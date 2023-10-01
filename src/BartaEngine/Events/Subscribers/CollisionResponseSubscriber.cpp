#include "pch.h"
#include "CollisionResponseSubscriber.h"

Barta::CollisionResponseSubscriber::CollisionResponseSubscriber(BartaEventLoggerInterface& eventLogger)
	: eventLogger(eventLogger) {

}

bool Barta::CollisionResponseSubscriber::handle(const CollisionEvent& event) {
	auto& [testResult, firstObject, secondObject] = event.getTestResult();
	if (testResult.staticCollision) {
		return true;
	}

	const auto& firstDynamics = firstObject->getDynamicsDTO();
	const auto& secondDynamics = secondObject->getDynamicsDTO();

	float massInverted = 0.;
	if (!firstDynamics.hasInfiniteMass) {
		massInverted += 1. / firstDynamics.mass;
	}

	if (!secondDynamics.hasInfiniteMass) {
		massInverted += 1. / secondDynamics.mass;
	}

	if (massInverted == 0.) {
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
	CollisionAwareInterface const*  dynamicsObject,
	Vector2f normVector
) const noexcept {
	const auto& oldDynamics = dynamicsObject->getDynamicsDTO();
	if (oldDynamics.hasInfiniteMass) {
		return;
	}

	//auto xd = DynamicsDTO(oldDynamics.velocity + normVector * (j / oldDynamics.mass), oldDynamics.hasInfiniteMass, oldDynamics.mass);
	this->eventLogger.logEvent(std::unique_ptr<const DynamicsChangeEvent>(new DynamicsChangeEvent(
		static_cast<DynamicsAwareInterface const*>(dynamicsObject),
		DynamicsDTO(oldDynamics.velocity + normVector * (j / oldDynamics.mass), oldDynamics.hasInfiniteMass, oldDynamics.mass)
	)));
}
