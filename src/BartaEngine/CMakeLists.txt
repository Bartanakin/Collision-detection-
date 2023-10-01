set(BARTA_ENGINE_INCLUDES "./")

add_library(${LIBRARY_NAME} STATIC
    "Application.cpp"
    "BartaObjectManager.cpp"
    "pch.cpp"
    "Application.h"
    "BartaObjectManager.h"
    "pch.h"
    "BartaObject.h"
    "ObjectManagerInterface.h"
    "ReduceableList.h"
)

# target_precompile_headers(${LIBRARY_NAME} PUBLIC
#     "pch.h"
# )

add_subdirectory(Collisions)
add_subdirectory(Dynamics)
add_subdirectory(Events)
add_subdirectory(Geometrics)
add_subdirectory(Graphics)
add_subdirectory(Hitbox)
add_subdirectory(Tests)

target_link_libraries(
    ${LIBRARY_NAME}
    PUBLIC 
    sfml-graphics
)

target_include_directories(${LIBRARY_NAME} PUBLIC ${BARTA_ENGINE_INCLUDES})

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        ${LIBRARY_NAME}
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

# if(${ENABLE_LTO})
#     target_enable_lto(
#         TARGE
#         ${LIBRARY_NAME}
#         ENABLE
#         ON)
# endif()

if(${ENABLE_CLANG_TIDY})
    set(CMAKE_CXX_COMPILE_OPTIONS_USE_PCH -Winvalid-pch -x c++-header -include <PCH_HEADER>)
    add_clang_tidy_to_target(${LIBRARY_NAME})
else()
    message(STATUS "Not activating clang-tidy")
endif()