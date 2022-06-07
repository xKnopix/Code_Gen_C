// g++ -o main.exe main.cpp xml_parser.cpp -IC:\xerces-c\include -LC:\xerces-c\lib -lxerces-c.dll -std=c++11
#include "xml_parser.h"
#include "check.h"
//Wichtig! Unter File Preferences Settings Extensions "Run Code configuration" "Executor Map" "Edit in settings.json" 
//nach g++ $file weg machen und dafür main.cpp xml_parser.cpp einfügen, sonst geht der code runner Button nicht mehr 
//hat den grund dass beim Compelieren alle Source Dateien mit angegeben werden müssen und nicht nur die main.cpp

int main() {
    xml_parser x;

    xml_parser::GetOptSetup data = x.GetDataStrctFromXML("Example.xml");

    cout << data.options.option[1].description << endl;

    check c;

    c.check_data(data);

    return 0;
}
