#pragma once
#include<Application.h>
#include"Player.h"
#include"Objects/GiantBlock.h"
#include"Ball.h"
#include"Dynamics/TimerInterface.h"
#include "ListsDefinitions.h"
#include "CustomEvents/CustomEventLogger.h"

class BartaGraph :public Barta::Application{
	void checkLogic() override;
public:
	BartaGraph(std::unique_ptr<Barta::TimerInterface> const);
    BartaGraph(const BartaGraph&) = delete;
    BartaGraph(BartaGraph&&) = delete;
    BartaGraph& operator=(const BartaGraph&) = delete;
	~BartaGraph() noexcept;

	static std::unique_ptr<Barta::TransformableInterface> createNewTransformableInstance();

private:
    std::unique_ptr<CustomEventLogger> customEventsLogger;

	Ball* ball1;
	Ball* ball2;
	Ball* ball3;

	Player* player;

	GiantBlock* upperBound;
	GiantBlock* leftBound;
	GiantBlock* bottomBound;
	GiantBlock* rightBound;

    BallList ballList;
    BombList bombList;
};

