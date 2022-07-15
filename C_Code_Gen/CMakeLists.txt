# CMakeList.txt: CMake-Projekt für "C_Code_Gen". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.

add_executable (C_Code_Gen "main.cpp" "pugixml-1.12/src/pugixml.cpp" "xml_parser.cpp" "xml_parser.h" "CodeGenerator.cpp" "CodeGenerator.h" "check.cpp" "check.h" "mainGenerator.cpp" "mainGenerator.h")

if (WIN32)
	configure_file("Example.xml" "Debug/Example.xml")
  configure_file("Example.xml" "Example.xml")
endif (WIN32)

if (UNIX)
    configure_file("Example.xml" "Example.xml")
endif (UNIX)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET C_Code_Gen PROPERTY CXX_STANDARD 20)
endif()

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
