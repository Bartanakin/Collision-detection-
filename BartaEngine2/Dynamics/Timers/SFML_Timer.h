#pragma once
#include "../TimerInterface.h"
#include <SFML/Graphics.hpp>

namespace Barta{

	class SFML_Timer : public TimerInterface{
	public:
		SFML_Timer();
		~SFML_Timer();

		float getElapsedTime() const;

	private:
		sf::Clock sf_clock;
	};
}

