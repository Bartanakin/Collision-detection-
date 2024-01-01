#pragma once
#include "Ball.h"
#include "CustomEvents/PostDynamicEventLogger.h"
#include "Dynamics/TimerInterface.h"
#include "ListsDefinitions.h"
#include "Player.h"
#include "Stages/StageInterface.h"
#include <Application.h>
#include <StaticObjectManager.h>

class BartaGraph :public Barta::Application{
	void checkLogic() override;
	void preGarbageCollect() override;
	void postDynamicUpdate() override;
    bool isRunning() const override;
public:
	BartaGraph(std::unique_ptr<Barta::TimerInterface> const);
    BartaGraph(const BartaGraph&) = delete;
    BartaGraph(BartaGraph&&) = delete;
    BartaGraph& operator=(const BartaGraph&) = delete;
	~BartaGraph() noexcept;

	static std::unique_ptr<Barta::TransformableInterface> createNewTransformableInstance();

private:
    std::unique_ptr<PostDynamicEventLogger> postDynamicEventLogger;

    CollisionEventsLogger collisionEventsLogger;
    CollisionCoreExecutor collisionExecutor;
    ListManager objectLists;

    SceneChangeEvent::SceneType currentSceneType;
    StageChangeEvent::StageID currentStageId;

    bool isRunning_v;
};

