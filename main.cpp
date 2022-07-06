// g++ -o main.exe main.cpp xml_parser.cpp -IC:\xerces-c\include -LC:\xerces-c\lib -lxerces-c.dll -std=c++11
#include "xml_parser.h"
#include "CodeGenerator.h"
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


    Code code = Code("FileName", "HeaderFileName", "parse", "getOptsParse", "79", "SampleUsage Here", "DER AUTOR");

    code.startForLoop("int i = 1; i<argc; i++");                                                                     //Durch jedes Argument einmal durch

    code.addArgument("1", "h", "help",         "2,3",   "printHelp", "Diese Hilfe ausgeben und beenden", "", "", "", "");
    code.addArgument("2", "v", "version",      "1,3",   "printVersion", "Gibt die Version des Programms aus und beendet", "Version", "", "", "");
    code.addArgument("",  "",  "out-path",     "1,2,3", "",         "Der Pfad wo das Ergebnis hingeneriert werden soll (sonst ins aktuelle Verzeichnis)", "OutputPath", "Required", "", "");
    code.addArgument("",  "",  "astyle-path",  "1,2,3", "",         "Der Pfad wo die Astyle executable gefunden werden kann", "AstylePath", "Required", "", "");
    code.addArgument("",  "",  "sign-per-line","1,2,3", "",         "Die Anzahl der Zeichen pro Linie fÃ¼r den Helptext. Ohne Argument wird der Standartwert genommen.", "SignPerLine", "optional", "Integer", "79");
    code.addArgument("",  "n", "only-if-newer","1,2,3", "",         "Generiert nur wenn die Eingangsdatei neuer ist wie die bereits generierte", "OnlyIfNewer", "", "", "");
    code.addArgument("",  "",  "no-format",    "1,2,3", "",         "Erzeugte Datei wird nicht formatiert", "NoFormat", "", "", "");
    code.addArgument("3", "",  "parse-only",   "1,2",   "ParseXML", "Parst die Datei einmal und beendet das Programm", "", "", "", "");
    code.endForLoop();                                                                                                  //For Schleife fertig, der  rest kommt in finalCode()

    cout << "CODE: " << endl << code.finalCode();                                                                       //Code ausgeben

    // Create and open a text file
    ofstream MyFile(R"(filename.cpp)");

    // Write to the file
    MyFile << code.finalCode();                                                                                         //Code in Datei schreiben

    // Close the file
    MyFile.close();

    return 0;
}
