cmake_minimum_required(VERSION 3.16)

project(Frontend VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appFrontend
    main.cpp
)

qt_add_qml_module(appFrontend
    URI Frontend
    VERSION 1.0
    QML_FILES
        Authorization.qml
        MainWorkspace.qml
        MainWindow.qml
        Registration.qml
        Settings.qml
        Profile.qml
        Rooms.qml
    SOURCES
        network_manager.h network_manager.cpp
        main_application.h main_application.cpp
        base_page.h base_page.cpp
        authorization_page.h authorization_page.cpp
        registration_page.h registration_page.cpp
        main_page.h main_page.cpp
        settings_page.h settings_page.cpp
        profile_page.h profile_page.cpp
        rooms_page.h rooms_page.cpp
)

add_subdirectory(DefaultElements)
add_subdirectory(MainWorkspaceElements)
add_subdirectory(GeneralElements)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appFrontend PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appFrontend
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appFrontend
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appFrontend
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
