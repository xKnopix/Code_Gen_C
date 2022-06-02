#include "xml_parser.h"
//Wichtig! Unter File Preferences Settings Extensions "Run Code configuration" "Executor Map" "Edit in settings.json" 
//nach g++ $file weg machen und dafür main.cpp xml_parser.cpp xml_parser.h einfügen, sonst geht der code runner Button nicht mehr 
//hat den grund dass beim Compelieren alle Dateien mit angegeben werden müssen und nicht nur die main.cpp

int main() {
    xml_parser x;

    xml_parser::GetOptSetup data = x.GetDataStrctFromXML("Example.xml");

    cout << data.options.option[1].description << endl;
    return 0;
}
