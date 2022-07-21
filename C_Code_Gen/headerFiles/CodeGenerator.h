// Autor: Jacob Hochbaum

#ifndef CODEGEN_H
#define CODEGEN_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

#include "xml_parser.h"

using namespace std;

/// Diese Klasse hilft etwas übersichtlicher Code zu generieren.
///
/// Mithilfe der Klasse Code und den eingebauten Funktionen kann lesbarer und übersichtlicher Code generiert werden, als nur über string addierung.
class Code
{
    /*
     * Diese Klasse soll dazu dienen, einfacher und ueberischtlicher
     * ein Programm zu schreiben, welches als output c++ Code hat
     *
     *
     *
     *
     *
     *
     */
private:
    struct internalMethod         ////internalMethod////
    {                             // In diesem Struct werden Informationen zu einer internen Methode gespeichert
        string methodName = "";   ////Methodname////
                                  // der Name der Methode, welcher auch beim Aufruf genutzt wird, OHNE KLAMMERN
        string methodCode = "";   ////methodCode////
                                  // der Code, welcher von der Methode ausgefuehrt werden soll
        string methodEnd = "}\n"; ////methodEnd////
                                  // String fuer die Lesbarkeit, beinhaltet lediglich "}" um die Methode abzuschliessen
        string returnType = "void";

        string expectedVars = "";

        string privacy = "";
    };

    struct externalMethod       ////internalMethod////
    {                           // In diesem Struct werden Informationen zu einer internen Methode gespeichert
        string methodName = ""; ////Methodname////
        // der Name der Methode, welcher auch beim Aufruf genutzt wird, OHNE KLAMMERN
        // string methodCode = "";                                                                                             ////methodCode////
        // der Code, welcher von der Methode ausgefuehrt werden soll
        // string methodEnd = "}\n";                                                                                           ////methodEnd////
        // String fuer die Lesbarkeit, beinhaltet lediglich "}" um die Methode abzuschliessen
        string returnType = "void";

        string expectedVars = "";

        string privacy = "";
    };

    // Deklaration aller Strings, die benoetigt werden, um den c++ Code zu generieren
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
                         "#include <iostream>\n" // Alle includes, die eventuell benoetigt werden,
                         "#include <vector>\n",  // im generierten Argument-Parser

        namespaceString = "using namespace std;\n",

           globalVariables = "",
           variableDefinitions = "vector<int> exclusions;\n" /////variableDefinitions////
                                 "int exitArg = 0;\n"        // Hier wird der String mit allen Variablen Deklarationen gespeichert
                                 "int noRef = -1;\n"
                                 "string refValues[63];\n"
                                 "vector<string> additionalParams;\n"
                                 "vector<string> argumentnames;\n"
                                 "vector<string> refValuesSorted;\n"
                                 "vector<vector<string>> exclusionValuesSorted;\n"
                                 "int signPerLineDefaultValue = 79;\n",

           returnIfWrongArgs = "if(exitArg > 0)\n"           ////returnIfWrongArgs*////
                               "{\n"                         // If-Else Code, um das den Argument-Parser zu beenden,
                               "cout << \"EXIT\" << endl;\n" // falls beim parsen der Argumente ein Fehler aufgetreten
                               "return;\n"                   // ist
                               "}\n",

           exclusionCheck, ////exclusionCheck////
                           // String, in welchem eine For-Schleife gespeichert wird,
                           // in welcher Alle uebergebenen Argumente durchgegangen werden
                           // und auf ungueltige kombinationen geprueft werden

        pathRequiredCheck, ////pathRequiredCheck///
                           // Wenn bei einem Argument hasArguments auf 'required' gesetzt ist
                           // wird in diesem String Code gespeichert, der ueberprueft, ob das naechste
                           // Argument mit '--' anfaengt, wenn ja, wird das Programm abgebrochen und
                           // es gibt einen fehler aus, da nur die 'Haupt-Argumente' mit '--' anfangen sollen

        convertToInt, ////convertToInt////
                      // Hier wird der Code gespeichert, in welchem in einem Try-Catch-Block
                      // probiert wird, den uebergebenen String in einen Integer umzuwandeln

        code, ////code////
              // String, in dem der zu generierende Code bei einer Instanziierung von Code()
              // gespeichert wird

        forLoopAllArgsStart = "for(int i = 1; i<argc; i++)\n{\n", ////forLoopAllArgs[Start/Close]////
        forLoopAllArgsClose = "}\n",                              // Fuer bessere Lesbarkeit generierte Strings, welche den Anfang und das Ende
                                                                  // einer For-Schleife enthalten, welche einemal alle, beim Programmaufruf
                                                                  // uebergebenen Argumente durch-iteriert

        handleArgs = forLoopAllArgsStart; ////handleArgs////
                                          // In handleArgs wird eine 2. For-Schliefe gespeichert, welche nach dem
                                          // die Argumente auf ihre Korrektheit ueberprueft wurden nochmals alle Argumente
                                          // durch-iteriert und nun auf die uebergebenen Argumente reagiert.

    // Deklaration aller Vektoren
    vector<internalMethod> internalMethods; ////internalMethods////
                                            // In diesem Vector werden alle Instanzen des Structs internalMethod gespeichert

    vector<externalMethod> externalMethods;
    internalMethod iM;

    bool authorCodeAdded = false;

public:
    /// Leerer Konstruktor fuer schnell zu generierende Code-Objekte.
    ///  \n Erstellt ein neuese leeres Coder-Objekt
    Code();

    /// Konstruktor, um das Code-Objekt fuer den Argument-Parser zu erstellen, dabei werden ein paar Strings bereits gesetzt.
    Code(string sourceFileName, string headerFileName, string nameSpace, string className, string signPerLine, string sampleUsage, string author);

private:
    // Alle Methoden mit dem Rueckgabewert 'void'

    /// Funktion, um dem code eines Code Objektes beliebigen Text hinzuzufuegen.
    ///
    /// Diese Funktion fuegt dem Code des Code-Objektes den Text in den runden Klammern hinzu.
    ///@param s Der String, der angehaengt werden soll
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
    /// Diese Funktion gibt den Code des Code Objektes als String zurueck.
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

    /// Funktion, um dem Code eines Code Objektes eine For-Schleife hinzuzufuegen.
    ///
    /// Diese Funktion fuegt dem Code des Code-Objektes eine For-Schleife hinzu.
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
    ///@attention Der Text in den runden Klammern der For-Schleife wird nicht ueberprueft, sondern direkt uebernommen, somit obliegt die ueberpruefung auf Korrektheit beim Programmierer!
    /// @see endForLoop() startIf() endIf()
    ///@author Jacob
    void startForLoop(string s);
    //##########################################

    /// Funktion, um dem Code eines Code Objektes das Ende einer For-Schleife hinzuzufuegen ('}').
    ///
    /// Diese Funktion fuegt dem Code des Code-Objektes das Ende einer For-Schleife hinzu, eigentlich nur eine geschweifte Klammer '}'.
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

    /// Funktion, um dem Code eines Code Objektes eine If-Verzweigung hinzuzufuegen.
    ///
    /// Diese Funktion fuegt dem Code des Code-Objektes eine If-Verzweigung hinzu.
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
    ///@attention Der Text in den runden Klammern der If-Verzweigung wird nicht ueberprueft, sondern direkt uebernommen, somit obliegt die ueberpruefung auf Korrektheit beim Programmierer!
    /// @see startForLoop() endForLoop() endIf()
    ///@author Jacob
    void startIf(string s);
    //##########################################

    /// Funktion, um dem Code eines Code Objektes das Ender einer If-Verzweigung hinzuzufuegen.
    ///
    /// Diese Funktion fuegt dem Code des Code-Objektes das Ender einer If-Verzweigung hinzu.
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

    /// Funktion, um einen String in Grossbuchstaben umzuwandeln.
    ///
    /// Diese Funktion wandelt einen String aus Gross- und Kleinbuchstaben in einen String, bei dem alle Kleinbuchstaben in Grossbuchstaben gewandelt wurden.
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
    /// Diese Funktion gibt als String den Code des zu generierenden Header-Files zurueck.
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
    /// Diese Funktion gibt als String den Code des zu generierenden Header-Files zurueck.
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
    /// Diese Funktion nimmt einen String und gibt einen Vector zurueck, der alle Teilstrings zwischen den Seperator-Zeichen als Elemente enthaelt.
    ///@param str der String, der aufgetrennt werden soll
    ///@param seperator der Char, der im uebergebenen String als Seperator dient
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
    /// Diese Funktion ist die Hauptfunktion der Klasse, da sie den Code fuer den zu erstellenden Argument-Parser aus dem XML-Objekt erstellt.
    ///@param data Das XML-Objekt
    ///@returns void
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// Code code;
    ///
    /// code.parse(data);
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Jacob
public:
    void parse(xml_parser::GetOptSetup data);
    //##########################################

    /// Funktion, die dem Argument-Parser ein Argument hinzufuegt.
    ///
    /// Diese Funktion wird fuer jede "Option" in der xml-Datei aufgerufen und erstellt Code, um das Argument, \n sollte es aufgerufen werden, ordungsgemaess auf Exclusons zu ueberpruefen und auszufuehren.
    ///@param ref der Wert, der in der xml bei der Option bei ref steht
    ///@param shortOpt der Wert, der in der xml bei der Option bei shortOpt steht
    ///@param longOpt der Wert, der in der xml bei der Option bei longOpt steht
    ///@param exclusion der Wert, der in der xml bei der Option bei exclusion steht
    ///@param connectToInternalMethod der Wert, der in der xml bei der Option bei connectToInternalMethod steht
    ///@param description der Wert, der in der xml bei der Option bei description steht
    ///@param interface der Wert, der in der xml bei der Option bei interface steht
    ///@param hasArguments der Wert, der in der xml bei der Option bei hasArguments steht
    ///@param convertTo der Wert, der in der xml bei der Option bei convertTo steht
    ///@param defaultValue der Wert, der in der xml bei der Option bei defaultValue steht
    ///@param connectToExternalMethod der Wert, der in der xml bei der Option bei connectToExternalMethod steht
    ///@param GetOptSetupsignPerLineDefaultValue der Wert, der in der xml bei der Option bei GetOptSetup signPerLine
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
private:
    void addArgument(const string ref = "",
                     const string shortOpt = "",
                     const string longOpt = "",
                     const string exclusion = "", // DONE
                     const string connectToInternalMethod = "",
                     const string description = "",
                     const string interface = "",
                     const string hasArguments = "", // DONE
                     const string convertTo = "",
                     const string defaultValue = "", // DONE
                     const string connectToExternalMethod = "",
                     const string GetOptSetupsignPerLineDefaultValue = "79"); // Funktion, die alle Argumente aus der xml annimmt
};

// int main();
#endif
