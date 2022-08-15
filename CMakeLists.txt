cmake_minimum_required(VERSION 3.15)
project(a5_5_913_Goia_Alexia)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:\\Qt\\6.2.4\\mingw_64\\lib\\cmake")

if(UNIX)
    set(CMAKE_PREFIX_PATH "~/Qt/6.2.4/gcc_64/lib/cmake")
endif(UNIX)

find_package(Qt6 COMPONENTS
    Core
    Gui
    Widgets
    REQUIRED)

add_executable(a5_5_913_Goia_Alexia
    "source files/main.cpp"
    "header files/DynamicArray.h"
    "source files/service.cpp"
    "header files/service.h"
    "source files/repo.cpp"
    "header files/repo.h"
    "source files/tutorial.cpp"
    "header files/tutorial.h"
    "source files/ui.cpp"
    "header files/ui.h"
    "source files/tests.cpp"
    "header files/tests.h"
    "header files/handlers.h"
    "source files/handlers.cpp"
    "header files/gui.h"
    "source files/gui.cpp")
target_link_libraries(a5_5_913_Goia_Alexia
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

if(WIN32)
    set(DEBUG_SUFFIX)
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")

    if(NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")

        if(NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif()
    endif()

    if(EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif()

    foreach(QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach(QT_LIB)
endif()