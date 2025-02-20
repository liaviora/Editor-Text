cmake_minimum_required(VERSION 3.19)
project(Editor LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Editor
    WIN32 MACOSX_BUNDLE
    main.cpp
    editor.cpp
    editor.h
    editor.ui
    editor.qrc



)

# Resources:
set(editor_resource_files
    "images/bold.png"
    "images/copy.png"
    "images/cut.png"
    "images/redo.png"
    "images/undo.png"
    "images/exit.png"
    "images/info.png"
    "images/italic.png"
    "images/newfile.png"
    "images/openfile.png"
    "images/paste.png"
    "images/save.png"
    "images/saveas.png"
    "images/underline.png"
    "images/icon.png"
)

qt_add_resources(Editor "editor"
    PREFIX
        "/rexallina"
    FILES
        ${editor_resource_files}
)

target_link_libraries(Editor
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS Editor
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Editor
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
