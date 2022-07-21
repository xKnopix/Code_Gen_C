//Author Michael Hornstein, Jacob Hochbaum, Johannes Muessig

#include "xml_parser.h"
#include "CodeGenerator.h"
#include "check.h"
#include "mainGenerator.h"
#include "CMakeGen.h"

int main()
{

    xml_parser x;
    xml_parser::GetOptSetup data = x.GetDataStrctFromXML("Example.xml");//gibt GetOptSetup Struct data zurück

    check c;
    c.check_data(data); //checkt die daten auf vollständigkeit
    data = c.sortData(data); //sortiert die optionen alphabetisch prio: shortOpt

    Code code;
    code.parse(data); //generiert den Code fuer den Parser

    mainGenerator m = mainGenerator(data); //Generiert die exampleMain.cpp unter beachtung der daten

    CMakeGen cm(data); //Generiert die CMakeLists.txt unter beachtung der daten

    return 0;
}