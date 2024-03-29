cmake_minimum_required(VERSION 3.16)

# Project/Library Names
set(PROJECT_NAME "run_sandbox")
set(LIBRARY_NAME "BartaEngine")
set(SANDBOX_NAME "BartaSandbox")
set(UNIT_TEST_NAME "BartaEngineUT")

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")
set(CMAKE_GENERATOR "Unix Makefiles")

project(
    ${PROJECT_NAME}
    VERSION 2.0.0
    LANGUAGES CXX)

# Options
add_compile_definitions(DEBUG=1)
add_compile_definitions(RELEASE=0)

option(ENABLE_WARNINGS "Enable to add warnings to a target." ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable to treat warnings as errors." OFF)

option(ENABLE_TESTING "Enable a Unit Testing build." OFF)
option(ENABLE_CLANG_TIDY "Enable to add clang tidy." OFF)

option(ENABLE_SANITIZE_ADDR "Enable address sanitize." OFF)
option(ENABLE_SANITIZE_UNDEF "Enable undefined sanitize." OFF)
option(ENABLE_SANITIZE_LEAK "Enable leak sanitize (Gcc/Clang only)." OFF)
option(ENABLE_SANITIZE_THREAD "Enable thread sanitize (Gcc/Clang only)." OFF)

option(ENABLE_CLANG_FORMAT "Enable to add clang-format." ON)
option(ENABLE_CMAKE_FORMAT "Enable to add cmake-format." ON)

option(ENABLE_LTO "Enable to add Link Time Optimization." OFF)

# CMAKE MODULES
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)
include(ConfigSafeGuards)
include(Tools)

if(ENABLE_WARNINGS)
    include(Warnings)
endif()

add_cmake_format_target()
add_clang_format_target()

if(ENABLE_SANITIZE_ADDR OR ENABLE_SANITIZE_UNDEF)
    include(Sanitizer)
    add_sanitizer_flags()
endif()

# if(ENABLE_LTO)
#     include(LTO)
# endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_subdirectory(src)

add_executable(${PROJECT_NAME} src/main.cpp
        src/Sandbox/Subscribers/SceneChangeSubscriber.cpp
        src/Sandbox/Subscribers/SceneChangeSubscriber.h
        src/BartaEngine/Events/Subscribers/HitboxPositionCheckSubscriberProxy.h
        src/Sandbox/Objects/Button.cpp
        src/Sandbox/Objects/Button.h
        src/BartaEngine/Graphics/SpriteBuilder/StringSpriteBuilder.cpp
        src/BartaEngine/Graphics/SpriteBuilder/StringSpriteBuilder.h
        src/BartaEngine/Graphics/SpriteBuilder/StringSprite.h
        src/Sandbox/Subscribers/ExitButtonSubscriber.cpp
        src/Sandbox/Subscribers/ExitButtonSubscriber.h
        src/Sandbox/Subscribers/ButtonHoverSubscriber.cpp
        src/Sandbox/Subscribers/ButtonHoverSubscriber.h
        src/Sandbox/Subscribers/StopGameSubscriber.cpp
        src/Sandbox/Subscribers/StopGameSubscriber.h
        src/Sandbox/Objects/StageSelectButton.cpp
        src/Sandbox/Objects/StageSelectButton.h
        src/Sandbox/Subscribers/StageSelectSubscriber.cpp
        src/Sandbox/Subscribers/StageSelectSubscriber.h
        src/Sandbox/Subscribers/Collisions/PlayerHitSubscriber.cpp
        src/Sandbox/Subscribers/Collisions/PlayerHitSubscriber.h
        src/Sandbox/Objects/Flash.cpp
        src/Sandbox/Objects/Flash.h
        src/Sandbox/CustomEvents/FlashMessageEvent.h
        src/Sandbox/Subscribers/FlashMessageSubscriber.cpp
        src/Sandbox/Subscribers/FlashMessageSubscriber.h
        src/Sandbox/Objects/Instruction.cpp
        src/Sandbox/Objects/Instruction.h
        src/Sandbox/Subscribers/InstructionButtonSubscriber.cpp
        src/Sandbox/Subscribers/InstructionButtonSubscriber.h
)
target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC 
    sfml-graphics
    ${LIBRARY_NAME}
    ${SANDBOX_NAME}
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()

install(
    TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

install(
    TARGETS ${SANDBOX_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib)

install(
    TARGETS ${LIBRARY_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib)