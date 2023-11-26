#include "BartaGraph.h"
#include "Dynamics/Timers/SFML_Timer.h"
#include "Dynamics/Timers/FrameLimitTimerProxy.h"
#include "Geometrics/Math/QuadraticEquation.h"
#include <iostream>


int main() {

	Barta::Application* app = new BartaGraph(std::make_unique<Barta::FrameLimitTimerProxy>(
		std::make_unique<Barta::SFML_Timer>(),
		0.0f
	));
	app->run();
	delete app;

	return 0;
}