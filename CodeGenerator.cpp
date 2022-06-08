#include <iostream>
#include <vector>
#include <fstream>
#include <string>

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
    };

    //Deklaration aller Strings, die benötigt werden, um den c++ Code zu generieren
    string  hFileName = "newFile.hpp",                                                                                  ////hFileName////
                                                                                                                        //der Name des zu generierenden H-Datei

            printHelpMethodCode,                                                                                        ////printHelpMethodCode////
                                                                                                                        //Code, der in die printHelp Methode eingesetzt wird

            includesString =        "#include <string>\n"                                                               ////includesString////
                                    "#include <iostream>\n"                                                             //Alle includes, die eventuell benötigt werden,
                                    "#include <Vector>\n"                                                               //im generierten Argument-Parser
                                    ""
                                    "using namespace std;\n",

            variableDefinitions =   "vector<int> exclusions;\n"                                                         /////variableDefinitions////
                                    "int exitArg = 0;\n"                                                                //Hier wird der String mit allen Variablen Deklarationen gespeichert
                                    "int noRef = -1;\n",

            returnIfWrongArgs =     "if(exitArg > 0)\n"                                                                 ////returnIfWrongArgs*////
                                    "{\n"                                                                               //If-Else Code, um das den Argument-Parser zu beenden,
                                    "cout << \"EXIT\" << endl;\n"                                                       //falls beim parsen der Argumente ein Fehler aufgetreten
                                    "return 0;\n"                                                                       //ist
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

            handleArgs = forLoopAllArgsStart;                                                                           ////handleArgs////
                                                                                                                        //In handleArgs wird eine 2. For-Schliefe gespeichert, welche nach dem
                                                                                                                        //die Argumente auf ihre Korrektheit überprüft wurden nochmals alle Argumente
                                                                                                                        //durch-iteriert und nun auf die übergebenen Argumente reagiert.

    //Deklaration aller Vektoren
    vector<internalMethod>  internalMethods;                                                                            ////internalMethods////
                                                                                                                        //In diesem Vector werden alle Instanzen des Structs internalMethod gespeichert

public:
    //Alle Methoden mit dem Rückgabewert 'void'
    void createInt(string varName, int value = 0)
    {
        /*
         * Es wird Code erstellt, welcher einen neuen Integer mit dem übergebenen namen und Wert erstellt
         */
        ///:param varName:   der Name der Integer Variablen, welche dem Code hinzugefügt werden soll
        ///:param value:     der Wert, welcher dem Integer bei der Initialisierung zugewiesen werden soll, default = 0

        string newLine = "int " + varName + " = " + to_string(value) + ";\n";
        code += newLine;
    }

    void setInt(string varName, int newValue)
    {
        /*
         * Es wird Code generiert, welcher einem bereits bestehenden Integer einen neuen Wert zuweist
         */
        ///:param varName:   der Name der Integer Variablen, welche verändert werden soll
        ///:param newValue:  der Wert, welcher dem Integer zugewiesen werden soll

        code += varName + " = " + to_string(newValue) + " ;\n";
    }

    void addToInt(string varName, int addValue = 0)
    {
        /*
         * Es wird Code generiert, welcher einem bereits bestehenden Integer einen neuen Wert zuweist
         */
        ///:param varName:   der Name der Integer Variablen, welche verändert werden soll
        ///:param addValue:  der Wert, welcher zu dem Integer hinzu addiert werden soll, default = 0

        code += varName + " += " + to_string(addValue) + " ;\n";
    }

    void createString(string varName, string value = "")
    {
        /*
         * Es wird Code erstellt, welcher einen neuen String mit dem übergebenen namen und Wert erstellt
         */
        ///:param varName:   der Name der String Variablen, welche dem Code hinzugefügt werden soll
        ///:param value:     der Wert, welcher dem Integer bei der Initialisierung zugewiesen werden soll, default = ""

        string newLine = "string " + varName + " = \"" + value + "\";\n";
        code += newLine;
    }

    void setString(string varName, string newValue)
    {
        /*
         * Es wird Code generiert, welcher einem bereits bestehenden String einen neuen Wert zuweist
         */
        ///:param varName:   der Name der String Variablen, welche verändert werden soll
        ///:param newValue:  die Zeichen, welche dem String zugewiesen werden sollen

        code += varName + " = \"" + newValue + "\" ;\n";
    }

    void addToString(string varName, string addValue = "")
    {
        /*
         * Es wird Code generiert, welcher einem bereits bestehenden Integer einen neuen Wert zuweist
         */
        ///:param varName:   der Name der String Variablen, welche verändert werden soll
        ///:param addValue:  der Wert, welcher zu dem String angehängt werden soll, default = ""

        code += varName + " += " + addValue + " ;\n";
    }

    void COUT(string message)
    {
        /*
         * Es wird Code generiert, welcher den übergebenen String auf der Konsole ausgibt
         */
        ///:param message: Der String, welcher später ausgegben werden soll

       code += "cout << \"" + message + "\" << endl;\n";
    }

    void addText(string s)
    {
        /*
         * Der übergebene String wird an den gesamt Code angehängt, benutzung auf eigene Gefahr :)
         */
        ///:param s: Der Code, welcher angehängt werden soll

        code += s;
    }

    void addSingleComment(string comment)
    {
        /*
         * Es wird Code generiert, welcher den übergebenen String als Kommentar an den gesamt Code anhängt
         */
        ///:param comment: Der Kommentar, welcher angehängt werden soll

        code += "//" + comment;
    }

    void addMultiLineComment(string comment)
    {
        /*
         * Es wird Code generiert, welcher den übergebenen String als Mehrzeilenkommentar an den gesamt Code anhängt
         */
        ///:param comment: Der Kommentar, welcher eingefügt werden soll

        code += "/*\n" + comment + "\n*/\n";
    }

    string getCode()
    {
        /*
         *Der generierte Code-String wird zurückgegeben
         */

        return code;
    }

    void startForLoop(string s)
    {
        /*
         * Es wird Code generiert, um eine for-Schleife im gesamt Code zu starten
         */
        ///:param s: Der Text der for-Schleife in den runden Klammern (!Muss Stimmen!)

        code += "for(" + s + ")\n{\n";
    }

    void endForLoop(){
        /*
         * NUR FÜR LESBARKEIT!
         * Es wird eine geschweifte Klammer angehängt, um eine begonnene for-Schleife zu schließen
         */
        code += "}\n";
    }

    void startIf(string s)
    {
        /*
         * Es wird Code generiert, um eine if-Verzweigung im gesamt Code zu starten
         */
        ///:param s: die Bedingung der if-Verzweigung als String (!Muss Stimmen!)
        code += "if(" + s + ")\n{\n";
    }

    void endIf()
    {
        /*
         * NUR FÜR LESBARKEIT!
         * Es wird eine geschweifte Klammer angehängt, um eine begonnene Verzweigung zu schließen
         */
        code += "}\n";
    }

    string finalCode()
    {
        /*
         * Der Finale Code wird erstellt und zurückgegeben
         * Es werden hierfür alle entstandenen zwischen Strings zusmmangefügt und zurückgegeben
         */
        ///:return: den gesamt Code {string}

        return includesString +
               createInternalMethods() +
               "int main(int argc, char* argv[])\n{\n" +
               variableDefinitions +
               forLoopAllArgsStart +
               exclusionCheck +
               forLoopAllArgsClose +
               pathRequiredCheck +
               convertToInt +
               returnIfWrongArgs +
               handleArgs +
               "}\nreturn 0;\n}\n";;
    }

    string createInternalMethods()
    {
        /*
         * Der Vektor mit allen Instanzen des Structs internalMethod wird durch-iteriert
         * und die Implementierung der Methoden erstellt
         * Alle Implementierungen werden in einem gesamt String gespeichert und zurückgegeben
         */

        ///:return: die Implementierung aller Methoden {string}

        Code methods = Code();

        string methodNames;

        for(int i = 0; i < internalMethods.size(); i++)
        {
            internalMethod iM = internalMethods[i];

            if(iM.methodName == "printHelp")                                                                            ////HelpMethode wird erstellt
            {
                iM.methodCode = printHelpMethodCode;
            }


            methods.addText("void " + iM.methodName + "()\n{\n");
            methods.addText(iM.methodCode);
            methods.addText(iM.methodEnd);

            methodNames += iM.methodName + "();\n";                                                                     /////////////////////////////////////////////////////////////////////////
                                                                                                                        ////H Datei
            ofstream MyFile(hFileName);

            // Write to the file
            MyFile << "Some hFile Text...";

            // Close the file
            MyFile.close();
                                                                                                                        ////H Datei Ende
            //cout << "NAMES: \n" << methodNames<< endl;                                                                /////////////////////////////////////////////////////////////////////////
        }


        return methods.code;
    }

    vector<string> split (string str, char seperator)
    {
        /*
         * Custom Split - Methode, um einen String bei einem bestimmten Char zu trennen
         * gibt einen Vektor mit allen Elementen zwischen den Seperatoren zurück
         */
        ///:param str: Der zu trennende String
        ///:param seperator: der Char, an dem der String getrennt werden soll
        ///:return: Vector mit allen Substrings {Vector<string>}

        vector<string> subStrings;
        int currIndex = 0, i = 0;
        int startIndex = 0, endIndex = 0;
        while (i <= str.length())
        {
            if (str[i] == seperator || i == str.length())
            {
                endIndex = i;
                string subStr = "";
                subStr.append(str, startIndex, endIndex - startIndex);
                subStrings.push_back(subStr);
                currIndex += 1;
                startIndex = endIndex + 1;
            }
            i++;
        }
        return subStrings;
    }

    void addArgument(string ref = "",
                     string shortOpt = "",
                     string longOpt = "",
                     string exclusion = "",                     //DONE
                     string connectToInternalMethod = "",
                     string description = "",
                     string interface = "",
                     string hasArguments = "",                  //DONE
                     string convertTo = "",
                     string defaultValue = ""                   //DONE
                                )                                                                                       //Funktion, die alle Argumente aus der xml annimmt
    {
        /*
         * Es wird zunächst ein String generiert, welcher in eine if-Abfrage eingefügt werden kann, um zu überprüfen,
         * ob das aktuelle Argument der Iteration dem gewünschten String entspricht (shortOpt/longOpt)
         *
         * Wenn "exclusion" gesetzt wurde, wir der übergeben String bei dem char ',' aufgetrennt
         * und es wird Code generiert, welcher nun prüft, ob die gesetzten Exclusions bereits existieren.
         * Anschließend wird Code generiert, welcher das Argument selbst "registriert" für zukünftige
         * exclusion - checks.
         */

        string codeArgParse;
        string ifStateStart;
        string nameCheckBool;

                                                                                                                        ////Generierung des bool-Strings
        if(longOpt != "" && shortOpt != "")                                                                             //wenn longOpt und shortOpt gesetzt sind
        {
            nameCheckBool = "string(argv[i]) == \"--" + shortOpt + "\" || string(argv[i]) == \"--" + longOpt + "\"";
        }
        else if(longOpt != "")                                                                                          //Wenn nur longOpt gesetzt ist
        {
            nameCheckBool = "string(argv[i]) == \"--" + longOpt + "\"";
        }
        else if(shortOpt != "")                                                                                         //wenn nur shortOpt gesetzt ist
        {
            nameCheckBool = "string(argv[i]) == \"--" + shortOpt + "\"";
        }
                                                                                                                        ///////////////////////////////////////////////////

        ifStateStart = "if(" + nameCheckBool +")\n{";                                                                   //if-Statement String build

        if(exclusion != "")                                                                                             ////exclusions////
        {

            vector<int> exclusions;                                                                                     ////exclusions////
                                                                                                                            //exclusions werden in dem Format "1,2,3,4,..." übergeben
                                                                                                                            //dieser String wird jeweils an einem Komma getrennt und die einzelnen Elemente
                                                                                                                            //in dem Vector exclusions als Integer gespeichert

            vector<string> exclusionStrings = split(exclusion, ',');                                                    //Der String wird aufgetrennt

            Code exclCode = Code();                                                                                     //Es wird eine instanz der Klasse Code erzeugt, um den zu generierenden Code
                                                                                                                        //lesbarer, bzw. übersichtlicher erstellen zu können

            string tempCode =  "vector<string> localExclusions = {";                                                    ////tempCode////
                                                                                                                        //wird benutzt, um Code zu generieren, welcher
                                                                                                                        //einen string-Vektor erstellt, mit allen Exclusions, die bei dem Argument,
                                                                                                                        //welches gerade "erstellt" wird, gesetzt sind

            for(int i = 0; i < exclusionStrings.size(); i++)
            {
                tempCode += "\"" + exclusionStrings[i] + "\"";

                if(i+1 != exclusionStrings.size())
                {
                    tempCode += ", ";
                }
            }

            tempCode += "};\n";
                                                                                                                        //Code zur Vektor-Generierung ist erstellt
            exclCode.addText(tempCode);                                                                                 //Code wird in in den Code zur Exclusion-Überprüfung eingefügt

            exclCode.startForLoop("int i = 0; i < exclusions.size(); i++");                                             //Code wird mit Einrückungen lesbar eingefügt
                exclCode.startForLoop("int j = 0; j < localExclusions.size(); j++");
                    exclCode.startIf("to_string(exclusions[i]) == localExclusions[j]");
                        exclCode.addText("cout << \"Es wurde eine ungültige Kombination von Argumenten angegeben!\" << endl;\n");
                        exclCode.addText("exitArg = 1;\n");
                    exclCode.endIf();
                exclCode.endForLoop();
            exclCode.endForLoop();

            exclCode.startIf("noRef == 0");
                exclCode.addText("cout << \"Es wurde ein Argument übergeben, dass Ref 1-3 nicht zulässt, --help ist somit verboten!\"<< endl;\n");
                exclCode.addText("exitArg = 1;\n");
            exclCode.endIf();

            exclCode.startIf("exitArg != 1");
            if(ref != "")
            {
                exclCode.addText("exclusions.push_back(" + ref + ");\n");                                               //Das eigene Argument wird "registriert"
            }
                exclCode.addText("noRef = 1;\n");
            exclCode.endIf();

        exclusionCheck += ifStateStart;
            exclusionCheck += exclCode.getCode();

            if(hasArguments == "Required" || hasArguments == "optional")
            {
                exclusionCheck +="if(i+1 != argc)\n{\n" + interface + "Str = argv[i+1];\n}\n";                          //Code Generierung um zusätzliche Argumente einzulesen, falls diese Möglich sein sollen
            }
        exclusionCheck += "}\n";



        }
                                                                                                                        ///////////////////////////////////////////////////////////////////////////
        if(hasArguments == "Required")                                                                                  //Code Generierung, um zu überprüfen, ob ein zusätzliches Argument angegeben wurde,
                                                                                                                        //wenn es required ist
        {
            Code pathCheckCode = Code();                                                                                ////pathCheckCode////
                                                                                                                        //Neue Instanz con Code() um zu generierenden Code zwischenzuspeichern

            variableDefinitions += "string " + interface + "Str;\n";

            pathCheckCode.startIf("!" + interface + "Str.empty() && " + interface + "Str.length() > 1");
                pathCheckCode.startIf("(" + interface + "Str.at(0) == '-' && " + interface + "Str.at(1) == '-') || " + interface + "Str.length() <= 1");
                    pathCheckCode.addText("cout << \"--" + longOpt + " benötigt einen Pfad als Argument!\" << endl;\n");
                    pathCheckCode.addText("exitArg = 1;\n");
                pathCheckCode.endIf();
            pathCheckCode.endIf();

            pathCheckCode.startIf(interface +"Str.length() == 1");
                pathCheckCode.addText("cout << \"" +longOpt +" benötigt einen Pfad als Argument!\" << endl;\n");
                pathCheckCode.addText("exitArg = 1;\n");
            pathCheckCode.endIf();

            pathRequiredCheck += pathCheckCode.getCode();
        }
                                                                                                                        /////////////////////////////////////////////////////////////////
        if(defaultValue != "")                                                                                          //Code Generierung, falls es default Parameter gibt
        {
            variableDefinitions += "string " + interface + "Str = \"" + defaultValue + "\";\n";
        }
                                                                                                                        //////////////////////////////////////////////////////////////////
                                                                                                                        //Code Generierung für convertToInt mit try-catch
        if(convertTo == "Integer")
        {
            string convertInt = "try\n{\nint " + interface + "Int = stol(" + interface + "Str);\n}\n";

            convertInt += "catch (invalid_argument const &e)\n{\n";
            convertInt += "cout << \"Bad input: invalid_argument thrown for " + longOpt + ", using default Value if given\" << endl;\n";
            convertInt += "exitArg = 1;\n}\n";

            convertInt += "catch (out_of_range const &e)\n{\n";
            convertInt += "cout << \"Integer overflow: out_of_range thrown for " + longOpt + ", using default Value if given\" << endl;\n";
            convertInt += "exitArg = 1;\n}\n";

            convertToInt += convertInt;
        }                                                                                                               ////////////////////////////////////////////////////////////////////////

        Code actOnArgs = Code();

        actOnArgs.startIf(nameCheckBool);
            if(connectToInternalMethod != "")                                                                           /////////////////////////////////////////////////////////////////////////
            {                                                                                                           //Code Generierung für connectToInternalMethod
                internalMethod iM = internalMethod();

                iM.methodName = connectToInternalMethod;
                iM.methodCode = "cout << \"" + description + "\" << endl;\n";
                //cout << "METHOD NAME IN I_M: " << iM.methodName << endl;

                internalMethods.push_back(iM);
                actOnArgs.addText(connectToInternalMethod + "();\n");
            }
            else
            {
                actOnArgs.addText("cout << \"Es wurde der Parameter --" + longOpt + " erfolgreich übergeben!\" << endl;\n");//Feedback print, wenn ein Argument angegeben wurde
                if(hasArguments != "")
                {
                    actOnArgs.addText("cout << \"Zusätzliche Argumente:\" << " + interface + "Str << endl;\n");         //Zusätzliche Argumente zur Überprüfung mit ausgeben
                }
            }
            actOnArgs.endIf();

            handleArgs += actOnArgs.code;                                                                               //zum gesamt Code hinzufügen

        printHelpMethodCode += "cout << \"[--" + longOpt + "]: " + description + "\" << endl;\n";                       //Die Description wird an einen globalen string hinzugefügt für die printHelp Methode
    }

};

int main() {
    /*
    std::cout << "Hello, World!" << std::endl;

    code.createInt("Anzahl", 5);
    code.createInt("testInt2", 7);
    code.COUT("Hallo Welt");
    code.createString("testStr", "Hallo");
    code.setInt("Anzahl", 3);
    code.setString("testStr", "Welt");
     */

    Code code = Code();

    code.startForLoop("int i = 1; i<argc; i++");                                                                        //Durch jedes Argument einmal durch

        code.addArgument("1", "h", "help", "2,3", "", "Diese Hilfe ausgeben und beenden", "", "", "", "");
        code.addArgument("2", "v", "version", "1,3", "printVersion", "Gibt die Version des Programms aus und beendet", "Version", "", "", "");
        code.addArgument("", "", "out-path", "1,2,3", "", "Der Pfad wo das Ergebnis hingenriert werden soll (sonst ins aktuelle Verzeichnis)", "OutputPath", "Required", "", "");
        code.addArgument("", "", "astyle-path", "1,2,3", "", "Der Pfad wo die Astyle executable gefunden werden kann", "AstylePath", "Required", "", "");
        code.addArgument("", "", "sign-per-line", "1,2,3", "", "Die Anzahl der Zeichen pro Linie für den Helptext. Ohne Argument wird der Standartwert genommen.", "SignPerLine", "optional", "Integer", "79");
        code.addArgument("", "n", "only-if-newer", "1,2,3", "", "Generiert nur wenn die Eingangsdatei neuer ist wie die bereits generierte", "OnlyIfNewer", "", "", "");
        code.addArgument("", "", "no-format", "1,2,3", "", "Erzeugte Datei wird nicht formatiert", "NoFormat", "", "", "");
        code.addArgument("3", "", "parse-only", "1,2", "ParseXML", "Parst die Datei einmal und beendet das Programm", "", "", "", "");
    code.endForLoop();                                                                                                  //For Schleife fertig, der  rest kommt in finalCode()

    cout << "CODE: " << endl << code.finalCode();                                                                       //Code ausgeben

    // Create and open a text file
    ofstream MyFile(R"(C:\Users\hochb\CLionProjects\filename.cpp)");

    // Write to the file
    MyFile << code.finalCode();                                                                                         //Code in Datei schreiben

    // Close the file
    MyFile.close();




    return 0;
}