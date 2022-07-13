# CMakeList.txt: CMake-Projekt für "DIS_Missile". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.

SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)

find_package(Boost 1.56 REQUIRED COMPONENTS
             date_time filesystem iostreams
            HINTS C:/boost_1_79_0/boost)

message("BOOST FOUND: ${Boost_FOUND}")
message("BOOST VERSION: ${Boost_VERSION}")
message("BOOST LIBS: ${Boost_LIBRARIES}")
message("BOOST DIRS: ${Boost_INCLUDE_DIR}")


add_executable (DIS_Missile "DIS_Missile.cpp" "DIS_Missile.h" "Libs/pugixml-1.12/src/pugixml.cpp" "Xml_Parser.cpp" "Xml_Parser.h" "Missile.cpp" "Missile.h" "SendMulticast.h" "SendMulticast.cpp")

target_link_libraries (DIS_Missile LINK_PUBLIC ${Boost_LIBRARIES})

add_subdirectory ("Libs/opendis")

target_link_libraries (DIS_Missile LINK_PUBLIC OpenDIS7)
target_link_libraries (DIS_Missile LINK_PUBLIC OpenDIS6)


if (WIN32)
add_custom_command(TARGET DIS_Missile POST_BUILD        # Adds a post-build event to DIS_Missile
    COMMAND ${CMAKE_COMMAND} -E copy_if_different       # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/config.xml"           # <--this is in-file
        $<TARGET_FILE_DIR:DIS_Missile>)                                          # <--this is out-file path

add_custom_command(TARGET DIS_Missile POST_BUILD        # Adds a post-build event to DIS_Missile
    COMMAND ${CMAKE_COMMAND} -E copy_if_different       # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/build/Libs/opendis/Debug/OpenDIS7.dll"           # <--this is in-file
        $<TARGET_FILE_DIR:DIS_Missile>)                                          # <--this is out-file path
endif (WIN32)

if (UNIX)
    configure_file("config.xml" "config.xml")
endif (UNIX)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DIS_Missile PROPERTY CXX_STANDARD 20)
endif()

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
