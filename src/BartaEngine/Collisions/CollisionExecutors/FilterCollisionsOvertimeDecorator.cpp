#include "pch.h"
#include "FilterCollisionsOvertimeDecorator.h"

Barta::FilterCollisionsOvertimeDecorator::FilterCollisionsOvertimeDecorator(
	std::unique_ptr<CollisionTestExecutorInterface> decoratedObject,
	TimerInterface& timer
) noexcept:
	CollisionTestExecutorDecorator(std::move(decoratedObject)),
	timer(timer)
{
}

Barta::CollisionTestExecutorInterface::ResultsList Barta::FilterCollisionsOvertimeDecorator::executeTests(
	const CollisionAwareInterface::CollidableList& collidableList
) {
	auto resultsList = this->decoratedObject->executeTests(collidableList);
	if (resultsList.empty()) {
		return resultsList;
	}

	float max_time = this->timer.getCurrentDeltaTime();
	for (const auto& result : resultsList) {
		if (std::get<1>(result)->getDynamicsDTO().hasInfiniteMass
			&& std::get<2>(result)->getDynamicsDTO().hasInfiniteMass) {
			continue;
		}

		if (std::get<0>(result).timePassed < max_time && !std::get<0>(result).staticCollision) {
			max_time = std::get<0>(result).timePassed;
		}
	}

	auto i = resultsList.begin();
	while (i != resultsList.end()) {
		if (std::get<0>(*i).timePassed > max_time) {
			i = resultsList.erase(i);

			continue;
		}

		i++;
	}

	this->timer.setCurrentDeltaTime(max_time);

	return resultsList;
}
