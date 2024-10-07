qt_add_library(MainApplication STATIC)

target_include_directories(MainApplication PUBLIC ../headers)
target_link_libraries(MainApplication Qt6::Quick)
target_sources(MainApplication PUBLIC
    ../headers/main_application.h
    ../headers/network_manager.h
    main_application.cpp
    network_manager.cpp
)
