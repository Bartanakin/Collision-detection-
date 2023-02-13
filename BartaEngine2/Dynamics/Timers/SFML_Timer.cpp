#include "SFML_Timer.h"

Barta::SFML_Timer::SFML_Timer() :
	sf_clock( sf::Clock() )
{}

Barta::SFML_Timer::~SFML_Timer(){}

float Barta::SFML_Timer::getElapsedTime() const{
	return this->sf_clock.getElapsedTime().asSeconds();
}
