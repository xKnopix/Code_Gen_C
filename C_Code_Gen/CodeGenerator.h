#ifndef CODEGEN_H
#define CODEGEN_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

#include "xml_parser.h"

using namespace std;

/// This is the brief description for this class.
///
/// This is the detailed description. More Stuff here.
class Code
{
    /*
     * Diese Klasse soll dazu dienen, einfacher und überischtlicher
     * ein Programm zu schreiben, welches als output c++ Code hat
     *
     *
     *
     *
     *
     *
     */

    struct internalMethod         ////internalMethod////
    {                             // In diesem Struct werden Informationen zu einer internen Methode gespeichert
        string methodName = "";   ////Methodname////
                                  // der Name der Methode, welcher auch beim Aufruf genutzt wird, OHNE KLAMMERN
        string methodCode = "";   ////methodCode////
                                  // der Code, welcher von der Methode ausgeführt werden soll
        string methodEnd = "}\n"; ////methodEnd////
                                  // String für die Lesbarkeit, beinhaltet lediglich "}" um die Methode abzuschließen
        string returnType = "void";

        string expectedVars = "";
    };

    struct externalMethod       ////internalMethod////
    {                           // In diesem Struct werden Informationen zu einer internen Methode gespeichert
        string methodName = ""; ////Methodname////
        // der Name der Methode, welcher auch beim Aufruf genutzt wird, OHNE KLAMMERN
        // string methodCode = "";                                                                                             ////methodCode////
        // der Code, welcher von der Methode ausgeführt werden soll
        // string methodEnd = "}\n";                                                                                           ////methodEnd////
        // String für die Lesbarkeit, beinhaltet lediglich "}" um die Methode abzuschließen
        string returnType = "void";

        string expectedVars = "";
    };

    // Deklaration aller Strings, die benötigt werden, um den c++ Code zu generieren
    string headerFileName = "NewFile.h", ////headerFileName////
                                         // der Name des zu generierenden H-Datei

        sourceFileName = "noSourceFileName",

           nameSpace = "noNameSpace",

           className = "noClassname",

           signPerLine = "79",

           helpMethod = "",

           sampleUsage = "",

           author = "anonymous",

           boolIsSetName = "",

           additionalParamVarName = "",

           unknownOptionMethodCall = "unknownOption(argv[i]);",

           filename = "newFile", // optional damit kiene fehler kommen

        printHelpMethodCode, ////printHelpMethodCode////
                             // Code, der in die printHelp Methode eingesetzt wird

        includesString = "#include <string>\n"   ////includesString////
                         "#include <iostream>\n" // Alle includes, die eventuell benötigt werden,
                         "#include <vector>\n",  // im generierten Argument-Parser

        namespaceString = "using namespace std;\n",

           globalVariables = "",
           variableDefinitions = "vector<int> exclusions;\n" /////variableDefinitions////
                                 "int exitArg = 0;\n"        // Hier wird der String mit allen Variablen Deklarationen gespeichert
                                 "int noRef = -1;\n"
                                 "string refValues[63];\n"
                                 "vector<string> additionalParams;\n",

           returnIfWrongArgs = "if(exitArg > 0)\n"           ////returnIfWrongArgs*////
                               "{\n"                         // If-Else Code, um das den Argument-Parser zu beenden,
                               "cout << \"EXIT\" << endl;\n" // falls beim parsen der Argumente ein Fehler aufgetreten
                               "return;\n"                   // ist
                               "}\n",

           exclusionCheck, ////exclusionCheck////
                           // String, in welchem eine For-Schleife gespeichert wird,
                           // in welcher Alle übergebenen Argumente durchgegangen werden
                           // und auf ungültige kombinationen geprüft werden

        pathRequiredCheck, ////pathRequiredCheck///
                           // Wenn bei einem Argument hasArguments auf 'required' gesetzt ist
                           // wird in diesem String Code gespeichert, der überprüft, ob das nächste
                           // Argument mit '--' anfängt, wenn ja, wird das Programm abgebrochen und
                           // es gibt einen fehler aus, da nur die 'Haupt-Argumente' mit '--' anfangen sollen

        convertToInt, ////convertToInt////
                      // Hier wird der Code gespeichert, in welchem in einem Try-Catch-Block
                      // probiert wird, den übergebenen String in einen Integer umzuwandeln

        code, ////code////
              // String, in dem der zu generierende Code bei einer Instanziierung von Code()
              // gespeichert wird

        forLoopAllArgsStart = "for(int i = 1; i<argc; i++)\n{\n", ////forLoopAllArgs[Start/Close]////
        forLoopAllArgsClose = "}\n",                              // Für bessere Lesbarkeit generierte Strings, welche den Anfang und das Ende
                                                                  // einer For-Schleife enthalten, welche einemal alle, beim Programmaufruf
                                                                  //übergebenen Argumente durch-iteriert

        handleArgs = forLoopAllArgsStart; ////handleArgs////
                                          // In handleArgs wird eine 2. For-Schliefe gespeichert, welche nach dem
                                          // die Argumente auf ihre Korrektheit überprüft wurden nochmals alle Argumente
                                          // durch-iteriert und nun auf die übergebenen Argumente reagiert.

    // Deklaration aller Vektoren
    vector<internalMethod> internalMethods; ////internalMethods////
                                            // In diesem Vector werden alle Instanzen des Structs internalMethod gespeichert

    vector<externalMethod> externalMethods;
    internalMethod iM;

    bool authorCodeAdded = false;

public:
    /// Leerer Konstruktor für schnell zu generierende Code-Objekte.
    ///  \n Erstellt ein neuese leeres Coder-Objekt
    Code();

    /// Konstruktor, um das Code-Objekt für den Argument-Parser zu erstellen, dabei werden ein paar Strings bereits gesetzt.
    Code(string sourceFileName, string headerFileName, string nameSpace, string className, string signPerLine, string sampleUsage, string author);

    // Alle Methoden mit dem Rückgabewert 'void'

    /// Funktion, um dem code eines Code Objektes beliebigen Text hinzuzufügen.
    ///
    /// Diese Funktion fügt dem Code des Code-Objektes den Text in den runden Klammern hinzu.
    ///@param s Der String, der angehängt werden soll
    ///@returns void
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// Code code;
    ///
    /// code.addtext("#include <iostream>\n"");
    /// code.addtext("#include <vector>\n"");
    ///
    /// cout << code.getCode << endl;
    ///
    /// // OUTPUT:
    ///
    /// #include <iostream>
    /// #include <vector>
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Jacob
    void addText(string s);
    //##########################################

    /// Funktion, um den Code aus dem Code Objekt als String zu erhalten.
    ///
    /// Diese Funktion gibt den Code des Code Objektes als String zurück.
    ///@returns string
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// Code code;
    ///
    /// code.addtext("#include <iostream>\n"");
    /// code.addtext("#include <vector>\n"");
    ///
    /// cout << code.getCode << endl;
    ///
    /// // OUTPUT:
    ///
    /// #include <iostream>
    /// #include <vector>
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Jacob
    string getCode();
    //##########################################

    /// Funktion, um dem Code eines Code Objektes eine For-Schleife hinzuzufügen.
    ///
    /// Diese Funktion fügt dem Code des Code-Objektes eine For-Schleife hinzu.
    /// \n In den runden Klammern steht ein String, der wie die Zeichen in den runden Klammern der zu erzeugenden For-Schleife aussieht
    ///@param s Die "Bedingung" der For-Schleife
    ///@returns void
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// Code code;
    ///
    /// code.startForLoop("int i = 0; i < 5; i++");
    ///     code.addtext("cout << i << endl;");
    /// code.endForLoop();
    ///
    /// cout << code.getCode << endl;
    ///
    /// // OUTPUT:
    ///
    /// for(int i = 0; i < 5; i++)
    /// {
    ///     cout << i << endl;
    /// }
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@attention Der Text in den runden Klammern der For-Schleife wird nicht überprüft, sondern direkt übernommen, somit obliegt die Überprüfung auf Korrektheit beim Programmierer!
    /// @see endForLoop() startIf() endIf()
    ///@author Jacob
    void startForLoop(string s);
    //##########################################

    /// Funktion, um dem Code eines Code Objektes das Ende einer For-Schleife hinzuzufügen ('}').
    ///
    /// Diese Funktion fügt dem Code des Code-Objektes das Ende einer For-Schleife hinzu, eigentlich nur eine geschweifte Klammer '}'.
    ///@returns void
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// Code code;
    ///
    /// code.startForLoop("int i = 0; i < 5; i++");
    ///     code.addtext("cout << i << endl;");
    /// code.endForLoop();
    ///
    /// cout << code.getCode << endl;
    ///
    /// // OUTPUT:
    ///
    /// for(int i = 0; i < 5; i++)
    /// {
    ///     cout << i << endl;
    /// }
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    /// @see startForLoop() startIf() endIf()
    ///@author Jacob
    void endForLoop();
    //##########################################

    /// Funktion, um dem Code eines Code Objektes eine If-Verzweigung hinzuzufügen.
    ///
    /// Diese Funktion fügt dem Code des Code-Objektes eine If-Verzweigung hinzu.
    /// \n In den runden Klammern steht ein Boolscher ausdruck, wie wenn man eine normale If-Verzweigung implementiert, nur als String.
    ///@param s Die "Bedingung" der If-Verzweigung
    ///@returns void
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// Code code;
    ///
    /// int a = 0;
    /// int b = 1;
    ///
    /// code.startIf("a < b");
    ///     code.addtext("cout << "a ist kleiner als b!" << endl;");
    /// code.endIf();
    ///
    /// cout << code.getCode << endl;
    ///
    /// // OUTPUT:
    ///
    /// if(a < b)
    /// {
    ///     cout << "a ist kleiner als b!" << endl;
    /// }
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@attention Der Text in den runden Klammern der If-Verzweigung wird nicht überprüft, sondern direkt übernommen, somit obliegt die Überprüfung auf Korrektheit beim Programmierer!
    /// @see startForLoop() endForLoop() endIf()
    ///@author Jacob
    void startIf(string s);
    //##########################################

    /// Funktion, um dem Code eines Code Objektes das Ender einer If-Verzweigung hinzuzufügen.
    ///
    /// Diese Funktion fügt dem Code des Code-Objektes das Ender einer If-Verzweigung hinzu.
    ///@returns void
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// Code code;
    ///
    /// int a = 0;
    /// int b = 1;
    ///
    /// code.startIf("a < b");
    ///     code.addtext("cout << "a ist kleiner als b!" << endl;");
    /// code.endIf();
    ///
    /// cout << code.getCode << endl;
    ///
    /// // OUTPUT:
    ///
    /// if(a < b)
    /// {
    ///     cout << "a ist kleiner als b!" << endl;
    /// }
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    /// @see startForLoop() endForLoop() startIf()
    ///@author Jacob
    void endIf();
    //###############################

    /// Funktion, um einen String in Großbuchstaben umzuwandeln.
    ///
    /// Diese Funktion wandelt einen String aus Groß- und Kleinbuchstaben in einen String, bei dem alle Kleinbuchstaben in Großbuchstaben gewandelt wurden.
    ///@param s Der String, welcher gewandelt werden soll
    ///@returns string
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// Code code;
    ///
    /// string myString = "Das ist ein Test";
    ///
    /// cout << code.capitalizeString(myString); << endl;
    ///
    /// // OUTPUT:
    /// //DAS IST EIN TEST
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Jacob
    string capitalizeString(string s);
    //##########################################

    /// Funktion, um den Code des zu generierenden Header-Files zu erhalten.
    ///
    /// Diese Funktion gibt als String den Code des zu generierenden Header-Files zurück.
    ///@param data Das xml-Objekt der zuvor geparsten xml-Datei
    ///@returns string
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// #include <ofstream>
    ///
    /// Code code;
    ///
    /// ofstream MyFile(data.headerFileName.content);
    /// MyFile << code.finalCode(data); // Code in Datei schreiben
    /// MyFile.close();
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Jacob
    string finalHeaderCode(xml_parser::GetOptSetup data);
    //##########################################

    /// Funktion, um den Code des zu generierenden Source-Code-Files zu erhalten.
    ///
    /// Diese Funktion gibt als String den Code des zu generierenden Header-Files zurück.
    ///@param data Das xml-Objekt der zuvor geparsten xml-Datei
    ///@returns string
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// #include <ofstream>
    ///
    /// Code code;
    ///
    /// ofstream MyFile(data.headerFileName.content);
    /// MyFile << code.finalCode(data); // Code in Datei schreiben
    /// MyFile.close();
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Jacob
    string finalCode(xml_parser::GetOptSetup data);
    //##########################################

    /// Funktion, um den Code zu generieren, der im generierten SourceCodeFile die internen Methoden definiert.
    ///
    /// Diese Funktion erstellt die Implementierung aller zuvor erstellten Methoden Objekte, \n die in dem Vektor internalMethods gespeichert sind.
    ///@param data Das xml-Objekt der zuvor geparsten xml-Datei
    ///@returns string
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// #include <ofstream>
    ///
    /// Code code;
    ///
    /// internalMethod iM;
    ///
    /// iM.methodName = "halloWelt"
    /// iM.returnType = "int"
    /// iM.expectedVars = "int a"
    /// iM.MethodCode = "cout << \"Hallo Welt!\" << endl; \n return a;"
    ///
    /// internalMethods.push_back(iM)
    ///
    /// cout << code.createInternalMethods() << endl;
    ///
    /// //OUTPUT:
    /// int halloWelt(int a)
    /// {
    /// cout << "Hallo Welt!" << endl;
    /// return a;
    /// }
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Jacob
    string createInternalMethods(xml_parser::GetOptSetup data);
    //##########################################

    /// Funktion, um einen String bei bestimmen Zeichen aufzutrennen.
    ///
    /// Diese Funktion nimmt einen String und gibt einen Vector zurück, der alle Teilstrings zwischen den Seperator-Zeichen als Elemente enthält.
    ///@param str der String, der aufgetrennt werden soll
    ///@param seperator der Char, der im übergebenen String als Seperator dient
    ///@returns vector<string>
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// #include <string>
    /// #include <vector>
    ///
    /// string myString = "5,2,8,4,9,1";
    ///
    ///  vector<string> splitString = split(myString);
    ///
    /// for(int i = 0; i < splitString.size(); i++)
    /// {
    ///     cout << splitString[i];
    /// }
    /// //OUTPUT:
    /// //5
    /// //2
    /// //8
    /// //4
    /// //9
    /// //1
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Jacob
    vector<string> split(string str, char seperator);
    //##########################################

    /// Funktion, die den Argument-Parser erstellt.
    ///
    /// Diese Funktion ist die Hauptfunktion der Klasse, da sie den Code für den zu erstellenden Argument-Parser aus dem XML-Objekt erstellt.
    ///@param data Das XML-Objekt
    ///@returns void
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// Code code;
    ///
    /// code.parse(data);
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Jacob
    void parse(xml_parser::GetOptSetup data);
    //##########################################

    /// Funktion, die dem Argument-Parser ein Argument hinzufügt.
    ///
    /// Diese Funktion wird für jede "Option" in der xml-Datei aufgerufen und erstellt Code, um das Argument, \n sollte es aufgerufen werden, ordungsgemäss auf Exclusons zu überprüfen und auszuführen.
    ///@param data Das XML-Objekt
    ///@returns void
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// Code code;
    ///
    /// code.addArgument(data.options.option[i].ref,
    ///                  data.options.option[i].shortOpt,
    ///                  data.options.option[i].longOpt,
    ///                  data.options.option[i].exclusion,
    ///                  data.options.option[i].connectToInternalMethod,
    ///                  data.options.option[i].description,
    ///                  data.options.option[i].interface,
    ///                  data.options.option[i].hasArguments,
    ///                  data.options.option[i].convertTo,
    ///                  data.options.option[i].defaultValue,
    ///                  data.options.option[i].connectToExternalMethod);
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Jacob
    void addArgument(string ref = "",
                     string shortOpt = "",
                     string longOpt = "",
                     string exclusion = "", // DONE
                     string connectToInternalMethod = "",
                     string description = "",
                     string interface = "",
                     string hasArguments = "", // DONE
                     string convertTo = "",
                     string defaultValue = "",             // DONE
                     string connectToExternalMethod = ""); // Funktion, die alle Argumente aus der xml annimmt
};

// int main();
#endif