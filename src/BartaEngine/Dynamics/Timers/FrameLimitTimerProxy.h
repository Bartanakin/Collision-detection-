#pragma once
#include "../TimerInterface.h"
#include <SFML/Graphics.hpp>

namespace Barta{

	class FrameLimitTimerProxy : public TimerInterface{
	public:
		/*
			Time in seconds
		*/
		FrameLimitTimerProxy( TimerInterface* const timer, float frameTime );
		~FrameLimitTimerProxy();

		float restart() override;

		float getElapsedTimeOnRestart() const override;

		void setCurrentDeltaTime( const float newDeltaTime ) override;

		float getCurrentDeltaTime() const override;

		void forward() override;

		bool finished() override;

	private:
		TimerInterface* const timer;

		const float frameTime;
	};
}

