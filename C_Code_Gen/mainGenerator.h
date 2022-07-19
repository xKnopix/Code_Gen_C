#ifndef MAINGENERATOR_H
#define MAINGENERATOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include "xml_parser.h"

///Diese Klasse ist da um eine examplemain.cpp zu erzeugen, um die implementierung des generierten Codes zu verdeutlichen
class mainGenerator{
public:
    ///Diese Methode wird aufgerufen um ein datenOpjekt (des Typs GetOptSetup) in eine examplemain.cpp zu schreiben
    ///@param data daten Objekt des Typs xml_parser::GetOptSetup
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// #include "mainGenerator.h"
    ///
    /// mainGenerator m = mainGenerator(data);
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Michael  
    mainGenerator(xml_parser::GetOptSetup data);
private:
    std::string output;
    void genMain();
    void genInheriteClass(xml_parser::Options options, xml_parser::ClassName classN);
    void useNameSpace(xml_parser::NameSpace namesp);
    void includes(xml_parser::HeaderFileName header);
};

#endif