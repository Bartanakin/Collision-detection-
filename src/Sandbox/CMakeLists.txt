set(SANDBOX_INCLUDES "./" "${CMAKE_SOURCE_DIR}/src/BartaEngine")

add_library(${SANDBOX_NAME} STATIC
    "Ball.cpp"
    "BartaGraph.cpp"
    "Bomb.cpp"
    "Gun.cpp"
    "Player.cpp"
    "ReloadMarker.cpp"
    "SimpleResourceContainer.cpp"
    "Wall.cpp"
        Stages/StageInterface.h
        Stages/StageOne.cpp
        Stages/StageOne.h
        Scenes/SceneInterface.h
        Scenes/GameScene.cpp
        Scenes/GameScene.h
        CustomEvents/SceneChangeEvent.h
        Stages/StageTwo.cpp
        Stages/StageTwo.h
        Repository/ObjectsRepository.cpp
        Repository/ObjectsRepository.h
        Scenes/LobbyScene.cpp
        Scenes/LobbyScene.h
        Stages/StageThree.cpp
        Stages/StageThree.h
        Stages/StageFour.cpp
        Stages/StageFour.h
        Stages/StageFive.cpp
        Stages/StageFive.h
        Scenes/SceneChangeDTO.cuh
        Scenes/InstructionScene.cpp
        Scenes/InstructionScene.h
        env.dist.h
)

add_subdirectory(CustomEvents)
add_subdirectory(Objects)
add_subdirectory(Subscribers)
add_subdirectory(Stages)

target_include_directories(${SANDBOX_NAME} PUBLIC ${SANDBOX_INCLUDES})

target_link_libraries(
    ${SANDBOX_NAME}
    PUBLIC
    sfml-graphics
    ${LIBRARY_NAME}
)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        ${SANDBOX_NAME}
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

# if(${ENABLE_LTO})
#     target_enable_lto(
#         TARGET
#         ${SANDBOX_NAME}
#         ENABLE
#         ON)
# endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target(${SANDBOX_NAME})
else()
    message(STATUS "Not activating clang-tidy in Sandbox")
endif()