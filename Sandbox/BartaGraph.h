#pragma once
#include<Application.h>
#include"Ball.h"

class BartaGraph :public Barta::Application{
	void checkLogic() override;
public:
	BartaGraph();

	~BartaGraph();

	static Barta::TransformableInterface* const createNewTransformableInstance();

private:
	Ball* ball1;
	Ball* ball2;
};

