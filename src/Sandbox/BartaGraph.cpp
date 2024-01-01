#include "BartaGraph.h"
#include "Collisions/CollisionDetectionStrategies/DynamicCollisionDetectionStrategy.h"
#include "CustomEvents/BallCreateEvent.h"
#include "CustomEvents/StageChangeEvent.h"
#include "Dynamics/ConstVelocityDynamicsUpdateStrategy.h"
#include "Geometrics/Math/BartaMathLibrary.h"
#include "Geometrics/SFML_Transformable.h"
#include "Graphics/SFML_GraphicsBridge.h"
#include "Objects/Flash.h"
#include "Repository/ObjectsRepository.h"
#include "Scenes/GameScene.h"
#include "Scenes/InstructionScene.h"
#include "Scenes/LobbyScene.h"
#include "SimpleResourceContainer.h"
#include "Stages/NoStage.h"
#include "Stages/StageFive.h"
#include "Stages/StageFour.h"
#include "Stages/StageOne.h"
#include "Stages/StageThree.h"
#include "Stages/StageTwo.h"
#include "Subscribers/Collisions/BallHitSubscriber.h"
#include "Subscribers/Collisions/BombCollisionSubscriber.h"
#include "Subscribers/Collisions/PlayerHitSubscriber.h"
#include "Subscribers/Collisions/PlayerWallSubscriber.h"
#include "Subscribers/Collisions/WallBounceSubscriber.h"
#include "Subscribers/FlashMessageSubscriber.h"
#include "Subscribers/SceneChangeSubscriber.h"
#include "Subscribers/StageChangeSubscriber.h"
#include "env.h"

/**
 * @deprecated
 */
const Barta::Vector2f gravity = {0.f, 250.f};

BartaGraph::BartaGraph(std::unique_ptr<Barta::TimerInterface> timer)
	: Application(
        Env::WINDOW_NAME,
		std::make_unique<Barta::SFML_GraphicsBridge>(
            std::make_unique<SimpleResourceContainer>(Env::REPOSITORY_DIR),
            Env::REPOSITORY_DIR
        ),
		std::make_unique<Barta::BartaEventLoggerInterface>(),
		std::make_unique<Barta::BartaEventLoggerInterface>(),
		std::make_unique<Barta::BartaObjectManager>(),
		std::move(timer),
		std::make_unique<Barta::ConstVelocityDynamicsUpdateStrategy>()
	),
    postDynamicEventLogger(std::make_unique<PostDynamicEventLogger>()),
    collisionEventsLogger({}),
    collisionExecutor(
        {{std::make_unique<Barta::DynamicCollisionDetectionStrategy>(std::make_unique<Barta::BartaMathLibrary>(), *this->timer)}},
        *this->timer
    ),
    objectLists({}),
    currentSceneType(SceneChangeEvent::SceneType::LOBBY),
    currentStageId(StageChangeEvent::StageID::NO_STAGE),
    isRunning_v(true)
{
    auto objectsRepository = ObjectsRepository(
        this->objectLists,
        *this->objectManager
    );
    StageArray stages;
    stages[StageChangeEvent::StageID::NO_STAGE] = std::make_unique<NoStage>();
    stages[StageChangeEvent::StageID::STAGE_I] = std::make_unique<StageOne>(
        this->objectLists,
        *this->objectManager,
        objectsRepository
    );
    stages[StageChangeEvent::StageID::STAGE_II] = std::make_unique<StageTwo>(
        this->objectLists,
        *this->objectManager,
        objectsRepository
    );
    stages[StageChangeEvent::StageID::STAGE_III] = std::make_unique<StageThree>(
        this->objectLists,
        *this->objectManager,
        objectsRepository
    );
    stages[StageChangeEvent::StageID::STAGE_IV] = std::make_unique<StageFour>(
        this->objectLists,
        *this->objectManager,
        objectsRepository
    );
    stages[StageChangeEvent::StageID::STAGE_V] = std::make_unique<StageFive>(
        this->objectLists,
        *this->objectManager,
        objectsRepository
    );

    SceneArray scenes;

    auto gameStage = std::make_unique<GameScene>(
        this->objectManager.get(),
        this->eventLogger.get(),
        this->postDynamicsEventLogger.get(),
        this->objectLists,
        this->collisionEventsLogger,
        this->postDynamicEventLogger.get(),
        this->currentStageId
    );
    auto lobbyStage = std::make_unique<LobbyScene>(
        this->objectManager.get(),
        this->eventLogger.get(),
        this->postDynamicEventLogger.get(),
        &this->isRunning_v
    );
    auto instructionScene = std::make_unique<InstructionScene>(
        this->objectManager.get(),
        this->eventLogger.get(),
        this->postDynamicEventLogger.get()
    );

    this->postDynamicEventLogger->logSubscriber(
        std::make_unique<StageChangeSubscriber>(
            std::move(stages),
            gameStage.get(),
            lobbyStage.get()
        )
    );

    scenes[SceneChangeEvent::SceneType::GAME] = std::move(gameStage);
    scenes[SceneChangeEvent::SceneType::LOBBY] = std::move(lobbyStage);
    scenes[SceneChangeEvent::SceneType::INSTRUCTION] = std::move(instructionScene);

    this->postDynamicEventLogger->logSubscriber(
        std::make_unique<SceneChangeSubscriber>(std::move(scenes), this->currentSceneType)
    );

    auto flash = new Flash({10.f, 10.f});
    this->objectManager->addNewObject(flash);

    this->postDynamicEventLogger->logSubscriber(
        std::make_unique<FlashMessageSubscriber>(*this->postDynamicEventLogger, flash)
    );
}

void BartaGraph::checkLogic() {
    (StaticCollisionLogger()).executeAndLog<CollisionEventsLogger, ListManager, CollisionCoreExecutor>(
        this->collisionEventsLogger,
        this->objectLists,
        this->collisionExecutor,
        *this->timer
    );

    this->collisionEventsLogger.runSubscribers();
}

void BartaGraph::postDynamicUpdate() {
    Application::postDynamicUpdate();

    this->postDynamicEventLogger->runSubscribers();
}

void BartaGraph::preGarbageCollect() {
    this->objectLists.StaticObjectManager<Bomb>::reduceDeleted();
    this->objectLists.StaticObjectManager<Ball>::reduceDeleted();
}

BartaGraph::~BartaGraph() {}

std::unique_ptr<Barta::TransformableInterface> BartaGraph::createNewTransformableInstance(){
	return std::unique_ptr<Barta::TransformableInterface>(new Barta::SFML_Transformable());
}
bool BartaGraph::isRunning() const {
    return this->isRunning_v;
}
