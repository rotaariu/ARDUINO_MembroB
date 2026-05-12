cmake_minimum_required(VERSION 3.16)
project(Interfaccia VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Network)  # ← aggiungi Network qui

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appInterfaccia
    main.cpp
)

qt_add_qml_module(appInterfaccia
    URI Interfaccia
    QML_FILES
        Main.qml
    SOURCES
        musicprovider.h
        musicprovider.cpp
)

set_target_properties(appInterfaccia PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appInterfaccia PRIVATE  # ← nome corretto
    Qt6::Quick
    Qt6::Network
)

install(TARGETS appInterfaccia
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)