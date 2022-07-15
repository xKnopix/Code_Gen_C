#ifndef MAINGENERATOR_H
#define MAINGENERATOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include "xml_parser.h"

class mainGenerator{
public:
    mainGenerator(xml_parser::GetOptSetup data);
private:
    std::string output;
    void genMain();
    void genInheriteClass(xml_parser::Options options, xml_parser::ClassName classN);
    void useNameSpace(xml_parser::NameSpace namesp);
    void includes(xml_parser::HeaderFileName header);
};

#endif