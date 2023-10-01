#pragma once
#include "../TimerInterface.h"
#include <SFML/Graphics.hpp>

namespace Barta{

	class SFML_Timer : public TimerInterface{
	public:
		SFML_Timer();
		~SFML_Timer();

		float restart() override;

		float getElapsedTimeOnRestart() const override;

		void setCurrentDeltaTime(const float newDeltaTime) override;

		float getCurrentDeltaTime() const override;

		void forward() override;

		bool finished() override;

	private:
		sf::Clock sf_clock;

		sf::Time remainingDeltaTime;

		sf::Time currentDeltaTime;
	};
}

