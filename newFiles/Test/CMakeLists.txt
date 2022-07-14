# CMakeList.txt: CMake-Projekt für "C_Code_Gen". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.

add_executable(Test "mainTestGenerated.cpp" "newFile.cpp" "newFile.h")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Test PROPERTY CXX_STANDARD 20)
endif()

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
