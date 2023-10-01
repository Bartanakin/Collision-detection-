#include "pch.h"
#include "CollisionTestExecutor.h"

Barta::CollisionTestExecutor::CollisionTestExecutor(
	std::unique_ptr<CollisionDetectionStrategyInterface> collisionDetectionStrategy
) noexcept:
	collisionDetectionStrategy(std::move(collisionDetectionStrategy)) {

}

Barta::CollisionTestExecutor::ResultsList Barta::CollisionTestExecutor::executeTests(
	const CollisionAwareInterface::CollidableList& collidableList
) {
	ResultsList collisionResults;

	auto i = collidableList.cbegin();
	while (i != collidableList.cend()) {
		auto j = i; j++;
		while (j != collidableList.cend()) {
			collisionResults.push_back({
				(*i)->getHitbox()->intersects(
					*((*j)->getHitbox()),
					*(this->collisionDetectionStrategy),
					(*i)->getDynamicsDTO() - (*j)->getDynamicsDTO()
				)
			, (*i), (*j)});
				
			j++;
		}

		i++;
	}

	return std::move(collisionResults);
}
