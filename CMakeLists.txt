cmake_minimum_required(VERSION 3.21)

set(CMAKE_PREFIX_PATH "C:/Qt/6.11.2/msvc2022_64")

project(V2p_gui
    VERSION 1.0
    LANGUAGES CXX
)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Qml
    Quick
)

qt_standard_project_setup()

# 실행 파일 생성
qt_add_executable(V2p_gui
    main.cpp
    vmware/VmxParser.cpp
    vmware/VmxParser.h
)

# QML 모듈
qt_add_qml_module(V2p_gui
    URI V2p_gui
    VERSION 1.0

    QML_FILES
        Constants.qml
        EventListModel.qml
        EventListSimulator.qml

        V2p_guiContent/App.qml
        V2p_guiContent/Screen01.ui.qml
)

target_link_libraries(V2p_gui
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
)