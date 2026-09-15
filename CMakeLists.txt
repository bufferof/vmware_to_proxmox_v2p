cmake_minimum_required(VERSION 3.21)

set(CMAKE_PREFIX_PATH "C:/Qt/6.11.2/msvc2022_64")

project(V2p_gui)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Qml
    Quick
)

qt_standard_project_setup()

qt_add_library(V2p_gui STATIC)

qt6_add_qml_module(V2p_gui
    URI "V2p_gui"
    VERSION 1.0

    QML_FILES
        "Constants.qml"
        "EventListModel.qml"
        "EventListSimulator.qml"
)