#ifndef CODEGEN_H
#define CODEGEN_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

#include "xml_parser.h"

using namespace std;



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

    struct internalMethod                                                                                               ////internalMethod////
    {                                                                                                                   //In diesem Struct werden Informationen zu einer internen Methode gespeichert
        string methodName = "";                                                                                             ////Methodname////
                                                                                                                            //der Name der Methode, welcher auch beim Aufruf genutzt wird, OHNE KLAMMERN
        string methodCode = "";                                                                                             ////methodCode////
                                                                                                                            //der Code, welcher von der Methode ausgeführt werden soll
        string methodEnd = "}\n";                                                                                           ////methodEnd////
                                                                                                                            //String für die Lesbarkeit, beinhaltet lediglich "}" um die Methode abzuschließen
        string returnType = "void";

        string expectedVars = "";
    };

    struct externalMethod                                                                                               ////internalMethod////
    {                                                                                                                   //In diesem Struct werden Informationen zu einer internen Methode gespeichert
        string methodName = "";                                                                                             ////Methodname////
        //der Name der Methode, welcher auch beim Aufruf genutzt wird, OHNE KLAMMERN
        //string methodCode = "";                                                                                             ////methodCode////
        //der Code, welcher von der Methode ausgeführt werden soll
        //string methodEnd = "}\n";                                                                                           ////methodEnd////
        //String für die Lesbarkeit, beinhaltet lediglich "}" um die Methode abzuschließen
        string returnType = "void";

        string expectedVars = "";
    };

    //Deklaration aller Strings, die benötigt werden, um den c++ Code zu generieren
            string headerFileName = "NewFile.h",                                                                                  ////headerFileName////
                                                                                                                        //der Name des zu generierenden H-Datei

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





            printHelpMethodCode,                                                                                        ////printHelpMethodCode////
                                                                                                                        //Code, der in die printHelp Methode eingesetzt wird

            includesString =        "#include <string>\n"                                                               ////includesString////
                                    "#include <iostream>\n"                                                             //Alle includes, die eventuell benötigt werden,
                                    "#include <Vector>\n",                                                               //im generierten Argument-Parser

            namespaceString =       "using namespace std;\n",

            globalVariables =       "",
            variableDefinitions =   "vector<int> exclusions;\n"                                                         /////variableDefinitions////
                                    "int exitArg = 0;\n"                                                                //Hier wird der String mit allen Variablen Deklarationen gespeichert
                                    "int noRef = -1;\n"
                                    "string refValues[63];\n",

            returnIfWrongArgs =     "if(exitArg > 0)\n"                                                                 ////returnIfWrongArgs*////
                                    "{\n"                                                                               //If-Else Code, um das den Argument-Parser zu beenden,
                                    "cout << \"EXIT\" << endl;\n"                                                       //falls beim parsen der Argumente ein Fehler aufgetreten
                                    "return;\n"                                                                         //ist
                                    "}\n",

            exclusionCheck,                                                                                             ////exclusionCheck////
                                                                                                                        //String, in welchem eine For-Schleife gespeichert wird,
                                                                                                                        //in welcher Alle übergebenen Argumente durchgegangen werden
                                                                                                                        //und auf ungültige kombinationen geprüft werden

            pathRequiredCheck,                                                                                          ////pathRequiredCheck///
                                                                                                                        //Wenn bei einem Argument hasArguments auf 'required' gesetzt ist
                                                                                                                        //wird in diesem String Code gespeichert, der überprüft, ob das nächste
                                                                                                                        //Argument mit '--' anfängt, wenn ja, wird das Programm abgebrochen und
                                                                                                                        //es gibt einen fehler aus, da nur die 'Haupt-Argumente' mit '--' anfangen sollen

            convertToInt,                                                                                               ////convertToInt////
                                                                                                                        //Hier wird der Code gespeichert, in welchem in einem Try-Catch-Block
                                                                                                                        //probiert wird, den übergebenen String in einen Integer umzuwandeln

            code,                                                                                                       ////code////
                                                                                                                        //String, in dem der zu generierende Code bei einer Instanziierung von Code()
                                                                                                                        //gespeichert wird

            forLoopAllArgsStart = "for(int i = 1; i<argc; i++)\n{\n",                                                   ////forLoopAllArgs[Start/Close]////
            forLoopAllArgsClose = "}\n",                                                                                //Für bessere Lesbarkeit generierte Strings, welche den Anfang und das Ende
                                                                                                                        //einer For-Schleife enthalten, welche einemal alle, beim Programmaufruf
                                                                                                                        //übergebenen Argumente durch-iteriert

            handleArgs = forLoopAllArgsStart;                                                                                               ////handleArgs////
                                                                                                                        //In handleArgs wird eine 2. For-Schliefe gespeichert, welche nach dem
                                                                                                                        //die Argumente auf ihre Korrektheit überprüft wurden nochmals alle Argumente
                                                                                                                        //durch-iteriert und nun auf die übergebenen Argumente reagiert.

    //Deklaration aller Vektoren
    vector<internalMethod>  internalMethods;                                                                            ////internalMethods////
                                                                                                                        //In diesem Vector werden alle Instanzen des Structs internalMethod gespeichert

    vector<externalMethod> externalMethods;
    internalMethod iM;

    bool authorCodeAdded = false;

public:
    Code();
    
    Code(string sourceFileName, string headerFileName, string nameSpace, string className,  string signPerLine, string sampleUsage, string author);

    //Alle Methoden mit dem Rückgabewert 'void'
    void createInt(const string& varName, int value = 0);

    void setInt(const string& varName, int newValue);

    void addToInt(const string& varName, int addValue = 0);

    void createString(const string& varName, string value = "");

    void setString(const string& varName, string newValue);

    void addToString(const string& varName, string addValue = "");

    void COUT(const string& message);

    void addText(string s);

    void addSingleComment(string comment);

    void addMultiLineComment(string comment);

    string getCode();

    void startForLoop(string s);

    void endForLoop();

    void startIf(string s);

    void endIf();

    string capitalizeString(string s);

    string finalHeaderCode();

    string finalCode();

    string createInternalMethods();

    vector<string> split (string str, char seperator);

    void parse(xml_parser::GetOptSetup data);

    string filename = "newFile"; //optional damit kiene fehler kommen

    void addArgument(string ref = "",
                     string shortOpt = "",
                     string longOpt = "",
                     string exclusion = "",                     //DONE
                     string connectToInternalMethod = "",
                     string description = "",
                     string interface = "",
                     string hasArguments = "",                  //DONE
                     string convertTo = "",
                     string defaultValue = "",                   //DONE
                     string connectToExternalMethod = ""
                                );                                                                          //Funktion, die alle Argumente aus der xml annimmt


};

//int main();
#endif