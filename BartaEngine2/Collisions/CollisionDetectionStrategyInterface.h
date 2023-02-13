#pragma once
#include"../BartaShapes/Circle.h"
#include"CheckCollisionVisitorInterface.h"

namespace Barta{
	class CollisionDetectionStrategyInterface{
	public:
		CollisionDetectionStrategyInterface() = default;
		virtual ~CollisionDetectionStrategyInterface() = default;

		virtual bool acceptCheckCollisionVisitor( const CheckCollisionVisitorInterface& checkCollisionVisitor ) const = 0;
	};
}

