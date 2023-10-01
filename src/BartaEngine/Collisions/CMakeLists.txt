add_subdirectory(CheckCollisionVisitors)
add_subdirectory(CollcionTestResult)
add_subdirectory(CollisionDetectionStrategies)
add_subdirectory(CollisionExecutors)

target_sources(${LIBRARY_NAME} PUBLIC 
    "CheckCollisionVisitorInterface.h"
    "CollisionAwareInterface.h"
    "CollisionDetectionStrategyInterface.h"
)