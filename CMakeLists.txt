cmake_minimum_required(VERSION 3.16)

project(102 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS PrintSupport)

#include_directories("${PROJECT_SOURCE_DIR}/lib/inc")
#find_library(exportLib NAMES exportLib.dll
#             PATHS ${PROJECT_SOURCE_DIR}/lib/release)

set(EXPORTLIB_DIR "EXPORTLIB_DIR" "C:/Users/stj.egurmericliler/Documents/exportLib")
set(EXPORTLIB_LIB_DIR ${EXPORTLIB_DIR} )

add_library(exportLib SHARED IMPORTED)
set_property(TARGET exportLib PROPERTY
            IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/release/exportLib.lib)

set_property(TARGET exportLib PROPERTY
            IMPORTED_IMPLIB ${PROJECT_SOURCE_DIR}/lib/release/exportLib.lib)

target_include_directories(exportLib INTERFACE
            ${PROJECT_SOURCE_DIR}/lib/inc)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(102
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        images.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 102 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(102 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(102
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(102
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Charts
        Qt${QT_VERSION_MAJOR}::PrintSupport
        exportLib
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.102)
endif()
set_target_properties(102 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS 102
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(102)
endif()
