set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/headers)
qt_add_library(MainApplication STATIC
    pages/CMakeLists.txt
    pages/main_page_contents/CMakeLists.txt)

add_subdirectory(pages)
target_include_directories(MainApplication PUBLIC ${INCLUDE_DIR})
target_link_libraries(MainApplication Qt6::Quick Pages)
target_sources(MainApplication PRIVATE
    ${INCLUDE_DIR}/main_application.h
    ${INCLUDE_DIR}/network_manager.h
    main_application.cpp
    network_manager.cpp
)
