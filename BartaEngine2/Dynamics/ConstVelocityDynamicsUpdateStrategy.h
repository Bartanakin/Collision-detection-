#pragma once
#include"DynamicsUpdateStrategyInterface.h"
#include<list>

namespace Barta{

	class ConstVelocityDynamicsUpdateStrategy : public DynamicsUpdateStrategyInterface{
	public:
		ConstVelocityDynamicsUpdateStrategy(
			float initialTime
		);

		virtual ~ConstVelocityDynamicsUpdateStrategy();
		
		virtual void subscribe( DynamicsAwareInterface* ) override;
		
		virtual void update( const float updateTime ) override;

	private:
		float savedTime;

		std::list<DynamicsAwareInterface*> objects;
	};
}