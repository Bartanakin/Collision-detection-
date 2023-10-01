#pragma once
#include "../../pch.h"
#include"../CollisionDetectionStrategyInterface.h"
#include"../../Dynamics/TimerInterface.h"
#include "../../Geometrics/Math/MathLibraryInterface.h"

namespace Barta{
	class DynamicCollisionDetectionStrategy : public CollisionDetectionStrategyInterface{
	public:
		DynamicCollisionDetectionStrategy( MathLibraryInterface* const mathLibrary, const TimerInterface& timer );
		virtual ~DynamicCollisionDetectionStrategy();

		virtual CollisionTestResult acceptCheckCollisionVisitor( const CheckCollisionVisitorInterface& checkCollisionVisitor ) const override;
	private:
		const TimerInterface& timer;

		MathLibraryInterface* const mathLibrary;
	};
}

