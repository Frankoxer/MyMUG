cmake_minimum_required(VERSION 3.28)
project(MyMUG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/Qt/5.14.2/mingw73_64")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED)

# 添加资源文件
#qt5_add_resources(RESOURCES code/View/resource.qrc)

add_executable(MyMUG
        main.cpp
        code/View/play/mainwindow.cpp
        code/View/play/mainwindow.h
        code/View/play/mainwindow.ui
        code/View/play/track.cpp
        code/View/play/track.h
        code/View/play/noteBlock.cpp
        code/View/play/noteBlock.h
        code/View/play/KeyEvent.h
        code/ViewModel/ViewModel.hpp
        code/App/GameApp.cpp
        code/App/GameApp.h
        code/Common/NoteInfo.h
        code/ViewModel/PlayThread.cpp
        code/ViewModel/PlayThread.h
        code/View/play/judgementLine.cpp
        code/View/play/comboBlock.cpp
        code/View/play/scoreblock.h
        code/View/play/scoreBlock.cpp
        code/View/play/scoreTitleBlock.cpp
        code/View/play/backgroundBlock.cpp
        code/View/play/accuracyBlock.cpp
        code/View/play/accuracyBlock.h
        code/View/play/albumBlock.cpp
        code/View/play/albumBlock.h
        code/View/play/levelBlock.cpp
        code/View/play/levelBlock.h
        code/View/play/maxComboBlock.cpp
        code/View/play/maxComboBlock.h
        code/View/play/performListBlock.cpp
        code/View/play/performListBlock.h
        code/View/play/ScoreEnd.cpp
        code/View/play/ScoreEnd.h
        code/ViewModel/MusicThread.cpp
        code/ViewModel/MusicThread.h
        code/View/select/selectwindow.cpp
        code/View/select/selectwindow.h
)

target_link_libraries(MyMUG
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Multimedia
        winmm
        stdc++fs
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets Multimedia)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()

# 修改自定义命令以将 audio 插件目录复制到 cmake-build-debug 文件夹的根目录下
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${QT_INSTALL_PATH}/plugins/audio"
        "${CMAKE_BINARY_DIR}/audio")

# 创建自定义目标以确保上述命令在构建后执行
add_custom_target(copy_audio_plugins ALL
        COMMAND ${CMAKE_COMMAND} -E echo "Copying Qt audio plugins..."
        DEPENDS ${PROJECT_NAME})
