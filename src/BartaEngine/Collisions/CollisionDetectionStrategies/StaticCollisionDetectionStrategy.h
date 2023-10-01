#pragma once
#include "../../pch.h"
#include"../CollisionDetectionStrategyInterface.h"
#include "../../Geometrics/Math/MathLibraryInterface.h"

namespace Barta{
	class StaticCollisionDetectionStrategy : public CollisionDetectionStrategyInterface{

	public:
		StaticCollisionDetectionStrategy( MathLibraryInterface* const );
		virtual ~StaticCollisionDetectionStrategy();

		virtual CollisionTestResult acceptCheckCollisionVisitor( const CheckCollisionVisitorInterface& checkCollisionVisitor ) const override;

	private:
		MathLibraryInterface* const mathLibrary;
	};
}

