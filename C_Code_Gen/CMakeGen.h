#ifndef CMAKEGEN_H
#define CMAKEGEN_H

#include <iostream>
#include "xml_parser.h"
#include <fstream>

///Diese Klasse erzeugt CMakeLits.txt um das Bauen der Beispielanwendung zu vereinfachen
class CMakeGen{
public:
    ///Diese Methode wird aufgerufen um ein datenOpjekt (des Typs GetOptSetup) zu einer CMakeLists.txt schreiben
    ///@param data daten Objekt des Typs xml_parser::GetOptSetup
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// #include "CMakeGen.h""
    ///
    ///  CMakeGen cm(data);
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Michael  
    CMakeGen(xml_parser::GetOptSetup data);
private:
    string output;
    void GenHeader();
    void GenAddExecutable(xml_parser::HeaderFileName header, xml_parser::SourceFileName source);
    void GenTail();
};

#endif