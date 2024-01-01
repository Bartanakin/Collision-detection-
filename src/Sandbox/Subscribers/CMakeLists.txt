add_subdirectory(Collisions)

target_sources(${LIBRARY_NAME} PUBLIC
    "BallCreateSubscriber.cpp"
    "GunMoveSubscriber.cpp"
    "GunShotSubscriber.cpp"
    "PlayerMoveSubscriber.cpp"
    "SceneChangeSubscriber.cpp"
    "StageChangeSubscriber.cpp"
)