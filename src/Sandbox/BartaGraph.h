#pragma once
#include<Application.h>
#include"Player.h"
#include"Objects/GiantBlock.h"
#include"Ball.h"
#include"Dynamics/TimerInterface.h"
#include "ListsDefinitions.h"
#include "CustomEvents/PostDynamicEventLogger.h"
#include <StaticObjectManager.h>

class BartaGraph :public Barta::Application{
	void checkLogic() override;
	void preGarbageCollect() override;
	void postDynamicUpdate() override;
public:
	BartaGraph(std::unique_ptr<Barta::TimerInterface> const);
    BartaGraph(const BartaGraph&) = delete;
    BartaGraph(BartaGraph&&) = delete;
    BartaGraph& operator=(const BartaGraph&) = delete;
	~BartaGraph() noexcept;

	static std::unique_ptr<Barta::TransformableInterface> createNewTransformableInstance();

private:
    std::unique_ptr<PostDynamicEventLogger> postDynamicEventLogger;

	Ball* ball1;
	Ball* ball2;
	Ball* ball3;

	Player* player;

	GiantBlock* upperBound;
	GiantBlock* leftBound;
	GiantBlock* bottomBound;
	GiantBlock* rightBound;

    CollisionEventsLogger collisionEventsLogger;
    CollisionCoreExecutor collisionExecutor;
    ListManager objectLists;
};

