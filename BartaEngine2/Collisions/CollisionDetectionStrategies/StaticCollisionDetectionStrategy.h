#pragma once
#include"../CollisionDetectionStrategyInterface.h"

namespace Barta{
	class StaticCollisionDetectionStrategy : public CollisionDetectionStrategyInterface{

	public:
		StaticCollisionDetectionStrategy();
		virtual ~StaticCollisionDetectionStrategy();

		virtual bool acceptCheckCollisionVisitor( const CheckCollisionVisitorInterface& checkCollisionVisitor ) const override;

	private:
	};
}

