#ifndef CMAKEGEN_H
#define CMAKEGEN_H

#include <iostream>
#include "xml_parser.h"
#include <fstream>

class CMakeGen{
public:
    CMakeGen(xml_parser::GetOptSetup data);
private:
    string output;
    void GenHeader();
    void GenAddExecutable(xml_parser::HeaderFileName header, xml_parser::SourceFileName source);
    void GenTail();
};

#endif