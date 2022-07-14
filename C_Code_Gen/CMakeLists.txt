# CMakeList.txt: CMake-Projekt für "C_Code_Gen". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.

add_executable (C_Code_Gen "main.cpp" "pugixml-1.12/src/pugixml.cpp" "xml_parser.cpp" "xml_parser.h" "filename.h" "filename.cpp" "CodeGenerator.cpp" "CodeGenerator.h" "check.cpp" "check.h")

if (WIN32)
add_custom_command(TARGET C_Code_Gen POST_BUILD        # Adds a post-build event to C_Code_Gen
    COMMAND ${CMAKE_COMMAND} -E copy_if_different       # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/Example.xml"           # <--this is in-file
        $<TARGET_FILE_DIR:C_Code_Gen>)                                          # <--this is out-file path
endif (WIN32)

if (UNIX)
    configure_file("Example.xml" "Example.xml")
endif (UNIX)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET C_Code_Gen PROPERTY CXX_STANDARD 20)
endif()

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
