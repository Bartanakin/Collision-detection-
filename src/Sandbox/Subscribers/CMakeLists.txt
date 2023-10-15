add_subdirectory(Collisions)

target_sources(${LIBRARY_NAME} PUBLIC
    "PlayerMoveSubscriber.cpp"
    "PlayerMoveSubscriber.h"
    "GunMoveSubscriber.cpp"
    "GunShotSubscriber.h"
    "GunShotSubscriber.cpp"
    "GunMoveSubscriber.h"
    "DynamicsChangeSubscriberProxy.cpp"
    "DynamicsChangeSubscriberProxy.h"
)