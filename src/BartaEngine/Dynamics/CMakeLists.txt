add_subdirectory(Timers)

target_sources(${LIBRARY_NAME} PUBLIC 
    "ConstVelocityDynamicsUpdateStrategy.cpp"
    "ConstVelocityDynamicsUpdateStrategy.h"
    "DynamicsAwareInterface.h"
    "DynamicsDTO.h"
    "DynamicsUpdateStrategyInterface.h"
    "TimerInterface.h"
)