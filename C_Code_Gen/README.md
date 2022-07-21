Main Page {#mainpage}
=========
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

Hinweis zur generierung der Getter Methoden: Da in den Requirements immer der longOpt-Name als name in den Methoden gewünscht war haben wir in unserem code wenn ein '-'
wie bei sign-per-line vorkommt, dieses '-' aus dem namen gelöscht und zu signperline (Bsp.: isSetsignperline()) gemacht.

Hinweis zur Angabe von zusätzlichen Argumenten:
in unserem generierten Argument-Parser werden zusätzliche Argumente ohne Zusätze einfach mit einem Leerzeichen getrennt hinter das Hauptargument geschrieben.
Bsp.: --out-path C:\Users\ --sign-per-line 10 -v
