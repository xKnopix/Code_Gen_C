Main Page {#mainpage}
=========

# C Code Gen

# Table of Contents
1. [Cmake](#Cmake)
    1. [Cmake Win32](#Cmake_Win32) 
    2. [Cmake Unix](#Cmake_Unix) 
3. [Build ExampleProject](#Build_ExampleProject)
4. [Use Parser](#Use_Parser)
5. [Hinweise](#Hinweise)

# Cmake
## Cmake_Win32

1. In Haupverzeichnis wechseln (dort wo der Ordner C_Code_Gen und CMakeLists.txt und Readme.md liegt)
2. neuen Ordner namens "build" anlegen
3. in build Ordner wechseln 
```
cd ./build
```
4. cmd in dem build Ordner öffnen 

5. "cmake -DCMAKE_PREFIX_PATH=C:\UserData\z180338\tools\xerces-c -G "MinGW Makefiles" .." in cmd eingeben 
```
cmake -DCMAKE_PREFIX_PATH=C:\UserData\z180338\tools\xerces-c -G "MinGW Makefiles" ..
```
6. "cmake --build ." eingeben
```
cmake --build .
```
Die Fertige exe kann dann unter build/C_Code_Gen/Debug gefunden werden



## Cmake_Unix

1. In Haupverzeichnis wechseln (dort wo der Ordner C_Code_Gen und CMakeLists.txt und Readme.md liegt)

2. neuen Ordner namens "build" anlegen
```
mkdir build
```
3. in build Ordner wechseln 
```
cd ./build
```
4. terminal in build ordner öffnen

5. "cmake .." in terminal eingeben wenn xerces nicht gefunden wurde dann "cmake -DCMAKE_PREFIX_PATH="opt/xerces-c" .." 
```
cmake ..
```
wenn xerces nicht gefunden wurde (bsp: opt/xerces-c)
```
cmake -DCMAKE_PREFIX_PATH="$Path to xerces install" .. 
```
"make" in terminal eingeben
```
make
```
Das fertige Programm kann dann unter /build/C_Code_Gen gefunden werden

# XML

in der Example.xml kann angepasst werden, wie der Code Generator Code erzeugt. Die Example.xml muss angepasst werden, wenn der Parser etwas anderes machen soll als die Beispiel Implementation

# Build_ExampleProject

Nach dem die C_Code_gen.exe (Win) oder C_Code_Gen ausgeführt wurde, wurden 4 neue Dateien erzeugt. (exampleMain.cpp, HeaderFileName.cpp, SourceFileName.h und CMakeLists.txt) diese Dateien sollten in einen Neuen Projektordner Kopiert werden. 
Der Neue Ordner sollte die Strucktur:

Projekt<br /> 
|<br /> 
|---exampleMain.cpp<br /> 
|---HeaderFileName.h<br /> 
|---SourceFileName.cpp<br /> 
|---CMakeLists.txt<br /> 

haben.

## 1. Externe Methoden Implementieren:
Hierzu wird die exampleMain.cpp geöffnet.
Dann wird nach einer Klasse namens "Klasse" gesucht, welche von dem angegeben ClassName erbt.
Hier sind nun beispiel Implementierungen vorhanden, die beliebig geändert werden können.

## 2. build

1. Im Projekt Ordner neuen Ordner namens build anlegen 
2. CMD (Win) oder Terminal(Unix) öffnen
3. In build Ordner wechseln 
```
cd ./build
```
4. "cmake .." eingeben
```
cmake ..
```
5. cmake --build . (Win) oder make (Linux) eingeben 
Windows
```
cmake --build .
```
Unix
```
make
```
6. Es sollte nun im "build" Ordner ein weiter Ordner "ExampleMain" sein, in welchem sich nun im Debug Ordner eine ExampleMain.exe befindet (Win).
7. Es sollte nun im "build" Ordner ein weiter Ordner "ExampleMain" sein, in welchem sich nun ein ExampleMain Programm befindet (Unix) 

# Use_Parser

Das Programm auszühren und dann mit --help die Hilfe ausgeben lassen
Win
```
ExampleMain.exe [args]
ExampleMain.exe -v
```
Unix
```
ExampleMain [args]
ExampleMain -v
```
# Hinweise

Hinweis zur generierung der Getter Methoden: Da in den Requirements immer der longOpt-Name als name in den Methoden gewünscht war haben wir in unserem code wenn ein '-'
wie bei sign-per-line vorkommt, dieses '-' aus dem namen gelöscht und zu signperline (Bsp.: isSetsignperline()) gemacht.

Hinweis zur Angabe von zusätzlichen Argumenten:
in unserem generierten Argument-Parser werden zusätzliche Argumente ohne Zusätze einfach mit einem Leerzeichen getrennt hinter das Hauptargument geschrieben.
Bsp.: --out-path C:\Users\ --sign-per-line 10 -v
