#include "pch.h"
#include "FilterNoCollisionResultsDecorator.h"

Barta::FilterNoCollisionResultsDecorator::FilterNoCollisionResultsDecorator(std::unique_ptr<CollisionTestExecutorInterface> decoratedObject) noexcept :
	CollisionTestExecutorDecorator(std::move(decoratedObject))
{
}

Barta::CollisionTestExecutorInterface::ResultsList Barta::FilterNoCollisionResultsDecorator::executeTests(
	const CollisionAwareInterface::CollidableList& collidableList
) {
	auto resultsList = this->decoratedObject->executeTests(collidableList);
	auto i = resultsList.begin();
	while (i != resultsList.end()) {
		if (i->collisionTestResult.collisionDetected) {
			i++;

			continue;
		}

		i = resultsList.erase(i);
	}

	return resultsList;
}
