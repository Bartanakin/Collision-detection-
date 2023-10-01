#pragma once
#include "pch.h"
#include "Geometrics/Vector2f.h"
#include "Graphics/BartaGraphicsBridgeInterface.h"
#include "Events/BartaEventLoggerInterface.h"
#include"ObjectManagerInterface.h"
#include "Dynamics/TimerInterface.h"
#include "Dynamics/DynamicsUpdateStrategyInterface.h"
#include "Collisions/CollisionDetectionStrategyInterface.h"
#include "Collisions/CollisionExecutors/CollisionTestExecutorInterface.h"

namespace Barta{
	class Application{
	public:
		Application( 
			BartaGraphicsBridgeInterface* const graphicsBridge,
			BartaEventLoggerInterface* const eventLogger,
			BartaEventLoggerInterface* const postDynamicsEventLogger,
			ObjectManagerInterface* const objectManager,
			TimerInterface* const timer,
			DynamicsUpdateStrategyInterface* const dynamicsUpdateStrategy,
			CollisionTestExecutorInterface* const collisionTestExecutor
		);

		virtual ~Application();

		virtual void run() final;

		virtual void checkLogic() = 0;

	protected:
		BartaGraphicsBridgeInterface* const graphicsBridge;
		BartaEventLoggerInterface* const eventLogger;
		BartaEventLoggerInterface* const postDynamicsEventLogger;
		ObjectManagerInterface* const objectManager;
		TimerInterface* const timer;
		DynamicsUpdateStrategyInterface* const dynamicsUpdateStrategy; 
		CollisionTestExecutorInterface* const collisionTestExecutor;
	};


}


