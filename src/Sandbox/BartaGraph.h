#pragma once
#include<Application.h>
#include"Block.h"
#include"Objects/GiantBlock.h"
#include"Ball.h"
#include"Dynamics/TimerInterface.h"

class BartaGraph :public Barta::Application{
	void checkLogic() override;
public:
	BartaGraph( Barta::TimerInterface* const );

	~BartaGraph();

	static Barta::TransformableInterface* const createNewTransformableInstance();

private:
	Ball* ball1;
	Ball* ball2;
	Ball* ball3;

	Block* block;

	GiantBlock* upperBound;
	GiantBlock* leftBound;
	GiantBlock* bottomBound;
	GiantBlock* rightBound;
};

