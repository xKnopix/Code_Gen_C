#Author Michael Hornstein

# CMakeList.txt: CMake-Projekt für "C_Code_Gen". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
if (UNIX)
	set(CMAKE_PREFIX_PATH "/opt/xerces-c")
endif (UNIX)
if (WIN32)
  #set(CMAKE_PREFIX_PATH "C/xerces-c")
endif (WIN32)

find_package(XercesC REQUIRED)

if(!${XercesC_FOUND})
  message("Xerces not Found!!! please use cmake -DCMAKE_PREFIX_PATH=\"path to xerces Root\"")
endif(!${XercesC_FOUND})

message("Foud Xerces? " ${XercesC_FOUND})
message("Xerces Verion " ${XercesC_VERSION})
message("Xerces Dirs " ${XercesC_INCLUDE_DIRS})
message("Xerces Libs " ${XercesC_LIBRARIES})

include_directories(${XercesC_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable (C_Code_Gen "sourceFiles/main.cpp" "sourceFiles/xml_parser.cpp" "headerFiles/xml_parser.h" "sourceFiles/CodeGenerator.cpp" "headerFiles/CodeGenerator.h" "sourceFiles/check.cpp" "headerFiles/check.h" "sourceFiles/mainGenerator.cpp" "headerFiles/mainGenerator.h" "headerFiles/CMakeGen.h" "sourceFiles/CMakeGen.cpp")

target_link_libraries(C_Code_Gen XercesC::XercesC)

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
