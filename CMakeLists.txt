cmake_minimum_required(VERSION 3.28)

project(lc3kit-ide
    VERSION 1.0.0
    LANGUAGES CXX
)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Qt
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Svg
)

# lc3kit (header-only, fetched at configure time)
include(FetchContent)
FetchContent_Declare(
    lc3kit
    GIT_REPOSITORY https://github.com/0xbad4/lc3kit.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(lc3kit)

# QScintilla
find_path(QSCINTILLA_INCLUDE_DIR
    NAMES Qsci/qsciscintilla.h
    PATH_SUFFIXES qt6
    HINTS
        /usr/include/${CMAKE_LIBRARY_ARCHITECTURE}
)
find_library(QSCINTILLA_LIBRARY NAMES qscintilla2_qt6)

if(NOT QSCINTILLA_INCLUDE_DIR OR NOT QSCINTILLA_LIBRARY)
    message(FATAL_ERROR
        "QScintilla for Qt6 not found. Install libqscintilla2-qt6-dev (Debian/Ubuntu) "
        "or qscintilla-qt6 (Arch), or pass -DQSCINTILLA_INCLUDE_DIR=... -DQSCINTILLA_LIBRARY=... directly."
    )
endif()

# Sources
set(SOURCES
    src/main.cpp
)

file(GLOB_RECURSE HEADERS
    CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.hpp"
)

# Executable
qt_add_executable(lc3kit-ide
    ${SOURCES}
    ${HEADERS}
)

# Windows: GUI subsystem, no console window.
# macOS: proper .app bundle so macdeployqt has something to work with.
if(WIN32)
    set_target_properties(lc3kit-ide PROPERTIES WIN32_EXECUTABLE TRUE)
elseif(APPLE)
    set_target_properties(lc3kit-ide PROPERTIES MACOSX_BUNDLE TRUE)
    set_target_properties(lc3kit-ide PROPERTIES
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "@executable_path/../Frameworks"
    )
endif()

# Include directories
target_include_directories(lc3kit-ide
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        ${QSCINTILLA_INCLUDE_DIR}
)

message(STATUS "QSCINTILLA_INCLUDE_DIR: ${QSCINTILLA_INCLUDE_DIR}")
message(STATUS "QSCINTILLA_LIBRARY: ${QSCINTILLA_LIBRARY}")

# Qt / lc3kit / QScintilla libraries
target_link_libraries(lc3kit-ide
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Svg
        lc3kit::lc3kit
        ${QSCINTILLA_LIBRARY}
)

# Strip qDebug() output from Release builds (QT_NO_DEBUG alone only
# disables Q_ASSERT, not qDebug()).
target_compile_definitions(lc3kit-ide PRIVATE
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)

# Compiler warnings
if(MSVC)
    target_compile_options(lc3kit-ide PRIVATE /W4)
else()
    target_compile_options(lc3kit-ide PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wno-unused-parameter
    )
endif()

# Install
include(GNUInstallDirs)

install(
    TARGETS lc3kit-ide
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    BUNDLE DESTINATION .
)

# Linux packaging (.deb / .rpm via CPack)
if(LINUX)
    set(CPACK_GENERATOR "DEB;RPM")
    set(CPACK_PACKAGE_NAME "lc3kit-ide")
    set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
    set(CPACK_PACKAGE_VENDOR "0xbad4")
    set(CPACK_PACKAGE_CONTACT "0xbad4 badr.eddin.py@gmail.com")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "LC-3 IDE built on lc3kit")
    set(CPACK_PACKAGING_INSTALL_PREFIX "/usr")

    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
    set(CPACK_DEBIAN_PACKAGE_SECTION "devel")

    set(CPACK_RPM_PACKAGE_AUTOREQPROV "yes")
    set(CPACK_RPM_PACKAGE_LICENSE "see LICENCE.md")

    include(CPack)
endif()