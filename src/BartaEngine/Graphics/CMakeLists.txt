add_subdirectory(SFML_Bridge)
add_subdirectory(SpriteBuilder)

target_sources(${LIBRARY_NAME} PUBLIC
    "BartaGraphicsBridgeInterface.h"
    "SFML_GraphicsBridge.cpp"
    "SFML_GraphicsBridge.h"
)