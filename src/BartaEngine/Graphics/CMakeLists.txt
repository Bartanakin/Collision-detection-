add_subdirectory(SFML_Bridge)

target_sources(${LIBRARY_NAME} PUBLIC
    "BartaGraphicsBridgeInterface.h"
    "Resource.h"
    "SFML_GraphicsBridge.cpp"
    "SFML_GraphicsBridge.h"
)