set(SANDBOX_INCLUDES "./" "${CMAKE_SOURCE_DIR}/src/BartaEngine")

add_library(${SANDBOX_NAME} STATIC
    "Ball.cpp"
    "Bomb.cpp"
    "Gun.cpp"
    "BartaGraph.cpp"
    "Player.cpp"
    "SimpleResourceContainer.cpp"
    "ReloadMarker.cpp"
)

add_subdirectory(Objects)
add_subdirectory(Subscribers)

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