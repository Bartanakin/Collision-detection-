#include "pch.h"
#include "ConstVelocityDynamicsUpdateStrategy.h"

void Barta::ConstVelocityDynamicsUpdateStrategy::update(
	DynamicsAwareInterface::DynamicsAwareList objectList, 
	const float deltaTime
) {
	for (auto& object : objectList) {
		object->move(object->getDynamicsDTO().velocity * deltaTime);
	}
}
