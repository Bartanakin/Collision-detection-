#include "pch.h"
#include "CollisionTestExecutorDecorator.h"

Barta::CollisionTestExecutorDecorator::CollisionTestExecutorDecorator(std::unique_ptr<CollisionTestExecutorInterface> decoratedObject) noexcept :
	decoratedObject(std::move(decoratedObject))
{
}

Barta::CollisionTestExecutorDecorator::ResultsList Barta::CollisionTestExecutorDecorator::executeTests(
	const CollisionAwareInterface::CollidableList& collidableList
) {
	return this->decoratedObject->executeTests(collidableList);
}
