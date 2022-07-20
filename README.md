# Code_Gen_C

Um das Projekt zu "builden":

Win:

In Haupverzeichnis wechseln (dort wo der Ordner C_Code_Gen und CMakeLists.txt und Readme.md liegt)

neuen Ordner namens "build" anlegen

in build Ordner wechseln 

cmd in dem build Ordner öffnen 

"cmake -DCMAKE_PREFIX_PATH=C:\UserData\z180338\tools\xerces-c -G "MinGW Makefiles" .." in cmd eingeben 

"cmake --build ." eingeben

Die Fertige exe kann dann unter build/C_Code_Gen/Debug gefunden werden



Linux/Unix:

In Haupverzeichnis wechseln (dort wo der Ordner C_Code_Gen und CMakeLists.txt und Readme.md liegt)

neuen Ordner namens "build" anlegen

in build Ordner wechseln 

terminal in build ordner öffnen

"cmake .." in terminal eingeben wenn xerces nicht gefunden wurde dann "cmake -DCMAKE_PREFIX_PATH="opt/xerces-c" .." 

"make" in terminal eingeben

Das fertige Programm kann dann unter /build/C_Code_Gen gefunden werden



Visual Studio Code und Cmake:

Plugins, Cmake suchen und installieren (von Microsoft)

Plugins, C++ suchen und installieren 

VSCode neustarten

Den Haupt Ordner in VisualStudioCode öffnen

Jetzt sollten von cmake unten links Buttons zum builden, Debugen und runnen sicht bar sein:
