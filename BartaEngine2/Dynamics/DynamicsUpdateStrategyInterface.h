#pragma once
#include "DynamicsAwareInterface.h"

namespace Barta{

	class DynamicsUpdateStrategyInterface{
	public:
		DynamicsUpdateStrategyInterface() = default;
		virtual ~DynamicsUpdateStrategyInterface() = default;

		virtual void subscribe( DynamicsAwareInterface* ) = 0;

		virtual void update( const float ) = 0;
	};
}