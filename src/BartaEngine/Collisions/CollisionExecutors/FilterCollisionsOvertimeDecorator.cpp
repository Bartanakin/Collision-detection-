#include "pch.h"
#include "FilterCollisionsOvertimeDecorator.h"

Barta::FilterCollisionsOvertimeDecorator::FilterCollisionsOvertimeDecorator(
	std::unique_ptr<CollisionTestExecutorInterface> decoratedObject,
	TimerInterface& timer
) noexcept:
	CollisionTestExecutorDecorator(std::move(decoratedObject)),
	timer(timer),
    lastCollisionResult({})
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
	auto i = resultsList.cbegin();
	while (i != resultsList.cend()) {
		if (i->object1->getDynamicsDTO().hasInfiniteMass
			&& i->object2->getDynamicsDTO().hasInfiniteMass) {
            i++;

			continue;
		}

        if ((*i) == this->lastCollisionResult) {
			i = resultsList.erase(i);

            continue;
        }

		if (
            i->collisionTestResult.timePassed < max_time
            && !i->collisionTestResult.staticCollision
        ) {
			max_time = i->collisionTestResult.timePassed;
		}

        i++;
	}

	i = resultsList.cbegin();
	while (i != resultsList.cend()) {
		if (i->collisionTestResult.timePassed > max_time) {
			i = resultsList.erase(i);

			continue;
		}

        if (!i->collisionTestResult.staticCollision)
            this->lastCollisionResult = *i;

		i++;
	}

	this->timer.setCurrentDeltaTime(max_time);

	return resultsList;
}
