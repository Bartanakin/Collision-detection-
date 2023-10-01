add_subdirectory(Events)
add_subdirectory(Subscribers)

target_sources(${LIBRARY_NAME} PUBLIC 
    "BartaEventLoggerInterface.h"
    "TemplateEventSubscriber.h"
)