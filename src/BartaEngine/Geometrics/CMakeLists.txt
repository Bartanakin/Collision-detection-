add_subdirectory(BartaShapes)
add_subdirectory(Math)

target_sources(${LIBRARY_NAME} PUBLIC 
    "Intersections.h"
    "Segment.cpp"
    "Segment.h"
    "SFML_Transformable.cpp"
    "SFML_Transformable.h"
    "TransformableInterface.h"
    "Vector2f.cpp"
    "Vector2f.h"
)