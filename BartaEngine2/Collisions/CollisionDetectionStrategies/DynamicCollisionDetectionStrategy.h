#pragma once
#include"../CollisionDetectionStrategyInterface.h"

namespace Barta{
	class DynamicCollisionDetectionStrategy : public CollisionDetectionStrategyInterface{
	public:
		DynamicCollisionDetectionStrategy();
		virtual ~DynamicCollisionDetectionStrategy();

		virtual bool acceptCheckCollisionVisitor( const CheckCollisionVisitorInterface& checkCollisionVisitor ) const override;

	private:
	};
}

