add_subdirectory(Collisions)

target_sources(${LIBRARY_NAME} PUBLIC
    "BallCreateSubscriber.cpp"
    "DynamicsChangeSubscriberProxy.cpp"
    "GunMoveSubscriber.cpp"
    "GunShotSubscriber.cpp"
    "PlayerMoveSubscriber.cpp"
)