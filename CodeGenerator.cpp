#include "CodeGenerator.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

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

    //Deklaration aller Strings, die benötigt werden, um den c++ Code zu generieren
                                                                               ////handleArgs////
                                                                                                                        //In handleArgs wird eine 2. For-Schliefe gespeichert, welche nach dem
                                                                                                                        //die Argumente auf ihre Korrektheit überprüft wurden nochmals alle Argumente
                                                                                                                        //durch-iteriert und nun auf die übergebenen Argumente reagiert.

    Code::Code()
    {

    }
    Code::Code(string sourceFileName, string headerFileName, string nameSpace, string className,  string signPerLine, string sampleUsage, string author)
    {
        Code::headerFileName = headerFileName;
        Code::nameSpace = nameSpace;
        Code::className = className;
        Code::signPerLine = signPerLine;
        Code::sampleUsage = sampleUsage;
        Code::author = author;
    }
    //Alle Methoden mit dem Rückgabewert 'void'
    void Code::createInt(const string& varName, int value)
    {
        /*
         * Es wird Code erstellt, welcher einen neuen Integer mit dem übergebenen namen und Wert erstellt
         */
        ///:param varName:   der Name der Integer Variablen, welche dem Code hinzugefügt werden soll
        ///:param value:     der Wert, welcher dem Integer bei der Initialisierung zugewiesen werden soll, default = 0

        string newLine = "int " + varName + " = " + to_string(value) + ";\n";
        code += newLine;
    }

    void Code::setInt(const string& varName, int newValue)
    {
        /*
         * Es wird Code generiert, welcher einem bereits bestehenden Integer einen neuen Wert zuweist
         */
        ///:param varName:   der Name der Integer Variablen, welche verändert werden soll
        ///:param newValue:  der Wert, welcher dem Integer zugewiesen werden soll

        code += varName + " = " + to_string(newValue) + " ;\n";
    }

    void Code::addToInt(const string& varName, int addValue)
    {
        /*
         * Es wird Code generiert, welcher einem bereits bestehenden Integer einen neuen Wert zuweist
         */
        ///:param varName:   der Name der Integer Variablen, welche verändert werden soll
        ///:param addValue:  der Wert, welcher zu dem Integer hinzu addiert werden soll, default = 0

        code += varName + " += " + to_string(addValue) + " ;\n";
    }

    void Code::createString(const string& varName, string value)
    {
        /*
         * Es wird Code erstellt, welcher einen neuen String mit dem übergebenen namen und Wert erstellt
         */
        ///:param varName:   der Name der String Variablen, welche dem Code hinzugefügt werden soll
        ///:param value:     der Wert, welcher dem Integer bei der Initialisierung zugewiesen werden soll, default = ""

        string newLine = "string " + varName + " = \"" + value + "\";\n";
        code += newLine;
    }

    void Code::setString(const string& varName, string newValue)
    {
        /*
         * Es wird Code generiert, welcher einem bereits bestehenden String einen neuen Wert zuweist
         */
        ///:param varName:   der Name der String Variablen, welche verändert werden soll
        ///:param newValue:  die Zeichen, welche dem String zugewiesen werden sollen

        code += varName + " = \"" + newValue + "\" ;\n";
    }

    void Code::addToString(const string& varName, string addValue)
    {
        /*
         * Es wird Code generiert, welcher einem bereits bestehenden Integer einen neuen Wert zuweist
         */
        ///:param varName:   der Name der String Variablen, welche verändert werden soll
        ///:param addValue:  der Wert, welcher zu dem String angehängt werden soll, default = ""

        code += varName + " += " + addValue + " ;\n";
    }

    void Code::COUT(const string& message)
    {
        /*
         * Es wird Code generiert, welcher den übergebenen String auf der Konsole ausgibt
         */
        ///:param message: Der String, welcher später ausgegben werden soll

       code += "cout << \"" + message + "\" << endl;\n";
    }

    void Code::addText(string s)
    {
        /*
         * Der übergebene String wird an den gesamt Code angehängt, benutzung auf eigene Gefahr :)
         */
        ///:param s: Der Code, welcher angehängt werden soll

        code += s;
    }

    void Code::addSingleComment(string comment)
    {
        /*
         * Es wird Code generiert, welcher den übergebenen String als Kommentar an den gesamt Code anhängt
         */
        ///:param comment: Der Kommentar, welcher angehängt werden soll

        code += "//" + comment;
    }

    void Code::addMultiLineComment(string comment)
    {
        /*
         * Es wird Code generiert, welcher den übergebenen String als Mehrzeilenkommentar an den gesamt Code anhängt
         */
        ///:param comment: Der Kommentar, welcher eingefügt werden soll

        code += "/*\n" + comment + "\n*/\n";
    }

    string Code::getCode()
    {
        /*
         *Der generierte Code-String wird zurückgegeben
         */

        return code;
    }

    void Code::startForLoop(string s)
    {
        /*
         * Es wird Code generiert, um eine for-Schleife im gesamt Code zu starten
         */
        ///:param s: Der Text der for-Schleife in den runden Klammern (!Muss Stimmen!)

        code += "for(" + s + ")\n{\n";
    }

    void Code::endForLoop(){
        /*
         * NUR FÜR LESBARKEIT!
         * Es wird eine geschweifte Klammer angehängt, um eine begonnene for-Schleife zu schließen
         */
        code += "}\n";
    }

    void Code::startIf(string s)
    {
        /*
         * Es wird Code generiert, um eine if-Verzweigung im gesamt Code zu starten
         */
        ///:param s: die Bedingung der if-Verzweigung als String (!Muss Stimmen!)
        code += "if(" + s + ")\n{\n";
    }

    void Code::endIf()
    {
        /*
         * NUR FÜR LESBARKEIT!
         * Es wird eine geschweifte Klammer angehängt, um eine begonnene Verzweigung zu schließen
         */
        code += "}\n";
    }

    string Code::finalCode()
    {
        /*
         * Der Finale Code wird erstellt und zurückgegeben
         * Es werden hierfür alle entstandenen zwischen Strings zusammengefügt und zurückgegeben
         */
        ///:return: den gesamt Code {string}

        return includesString +
               "namespace " + nameSpace + "\n" +
               "{\n" +
                    "class " + className + "\n" +
                    "{\n" +
                        globalVariables +
                        createInternalMethods() +
                        "void parse(int argc, char* argv[])\n"
                        "{\n" +
                            variableDefinitions +

                            forLoopAllArgsStart +
                                exclusionCheck +
                            forLoopAllArgsClose +

                            pathRequiredCheck +
                            convertToInt +
                            returnIfWrongArgs +
                            handleArgs +"}\n"
                        "}\n"
                    "};\n"
                    "}\n";
    }

    string Code::createInternalMethods()
    {
        /*
         * Der Vektor mit allen Instanzen des Structs internalMethod wird durch-iteriert
         * und die Implementierung der Methoden erstellt
         * Alle Implementierungen werden in einem gesamt String gespeichert und zurückgegeben
         */

        ///:return: die Implementierung aller Methoden {string}

        Code methods = Code();

        string methodNames;

        ///////////////////////myPrint für signPerLine erstellen

        internalMethod myPrint = internalMethod();
        myPrint.methodName = "myPrint";
        myPrint.methodCode =
                "int lineLength = newLineChecker;\n"
                "for (auto i = 0; i != myString.size(); ++i)\n"
                "{\n"
                "if (i == newLineChecker)\n"
                "{\n"
                "newLineChecker += lineLength;\n"
                "cout << endl;\n"
                "}\n"

                "cout << myString[i];\n"
                "}\n";

        methods.addText("void " + myPrint.methodName + "(string myString, int newLineChecker)\n{\n");
        methods.addText(myPrint.methodCode);
        methods.addText(myPrint.methodEnd);

        for(int i = 0; i < internalMethods.size(); i++)
        {
            internalMethod iM = internalMethods[i];

            if(iM.methodName == "printHelp")                                                                            ////HelpMethode wird erstellt
            {
                printHelpMethodCode += "myPrint(\"Author: " + author + "\", " + signPerLine + ");\n";
                iM.methodCode = "cout<<\"" + sampleUsage + "\"<< endl;\n" + printHelpMethodCode;

                methods.addText("protected: virtual void " + iM.methodName + "(int signPerLine)\n{\n");
                methods.addText(iM.methodCode);
                methods.addText(iM.methodEnd);

                methodNames += iM.methodName + "();\n";

            }
            else
            {
            methods.addText(iM.returnType + " " + iM.methodName + "(" + iM.expectedVars + ")\n{\n");
            methods.addText(iM.methodCode);
            methods.addText(iM.methodEnd);

            methodNames += iM.methodName + "();\n";                                                                     /////////////////////////////////////////////////////////////////////////
            }                                                                                                           ////H Datei
            ofstream MyFile(headerFileName);

            // Write to the file
            MyFile << "Some hFile Text...";

            // Close the file
            MyFile.close();
                                                                                                                        ////H Datei Ende
            //cout << "NAMES: \n" << methodNames<< endl;                                                                /////////////////////////////////////////////////////////////////////////
        }


        return methods.code;
    }

    vector<string> Code::split (string str, char seperator)
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

    void Code::addArgument(string ref,
                     string shortOpt,
                     string longOpt,
                     string exclusion,                     //DONE
                     string connectToInternalMethod,
                     string description,
                     string interface,
                     string hasArguments,                  //DONE
                     string convertTo,
                     string defaultValue,                   //DONE
                     string connectToExternalMethod
                                )                                                                          //Funktion, die alle Argumente aus der xml annimmt
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
        string reference;
        size_t found = longOpt.find('-');
        if(found != string::npos)
        {
            reference = longOpt;
            reference.erase(remove(reference.begin(), reference.end(), '-'), reference.end()); //remove A from string
            cout << "lOpt: "<< longOpt <<", reference: " << reference << endl;
            cout << "found '-' in " << longOpt << endl;
        }
        else if(interface != ""){
            reference = interface;
        }
        else if(longOpt != "")
        {
            reference = longOpt;
        }
        else if(shortOpt != "")
        {
            reference = shortOpt;
        }
        if(reference == "")
        {
            cerr << "Fehler beim Parsen der xml-Datei, etwas scheint mit shortOpt, longOpt und interface nicht in Ordnung zu sein! bei: " << longOpt << endl;
        }

        string codeArgParse;
        string ifStateStart;
        string nameCheckBool;

        boolIsSetName = "bool" + interface;                                                                                                                ////Generierung des bool-Strings
        if(longOpt != "" && shortOpt != "")                                                                             //wenn longOpt und shortOpt gesetzt sind
        {
            nameCheckBool = "string(argv[i]) == \"-" + shortOpt + "\" || string(argv[i]) == \"--" + longOpt + "\"";
        }
        else if(longOpt != "")                                                                                          //Wenn nur longOpt gesetzt ist
        {
            nameCheckBool = "string(argv[i]) == \"--" + longOpt + "\"";
        }
        else if(shortOpt != "")                                                                                         //wenn nur shortOpt gesetzt ist
        {
            nameCheckBool = "string(argv[i]) == \"-" + shortOpt + "\"";
        }
                                                                                                                        ///////////////////////////////////////////////////

        ifStateStart = "if(" + nameCheckBool +")\n{\n";                                                                   //if-Statement String build

        if(exclusion != "")                                                                                             ////exclusions////
        {

            vector<int> exclusions;                                                                                     ////exclusions////
                                                                                                                            //exclusions werden in dem Format "1,2,3,4,..." übergeben
                                                                                                                            //dieser String wird jeweils an einem Komma getrennt und die einzelnen Elemente
                                                                                                                            //in dem Vector exclusions als Integer gespeichert

            vector<string> exclusionStrings = split(exclusion, ',');                                        //Der String wird aufgetrennt

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
            exclCode.addText(tempCode);                                                                              //Code wird in in den Code zur Exclusion-Überprüfung eingefügt

            exclCode.startForLoop("int i = 0; i < exclusions.size(); i++");                                          //Code wird mit Einrückungen lesbar eingefügt
                exclCode.startForLoop("int j = 0; j < localExclusions.size(); j++");
                    exclCode.startIf("to_string(exclusions[i]) == localExclusions[j]");
                        //exclCode.addText("cout << \"Es wurde eine ungültige Kombination von Argumenten angegeben!\" << endl;\n");

            if(interface != "")
            {
                exclCode.addText("cerr << \"" + interface + " und \"<< refValues[exclusions[i]]<<\" sind nicht zusammen erlaubt!\" << endl;\n");
            }///// IF Abfrage ob Interface, longOpt oder shortOpt -> Ausgabe: x nicht erlauibt mit refValues[ref]
            else if (longOpt != "")
            {
                exclCode.addText("cerr << \"" + longOpt + " und \"<< refValues[exclusions[i]]<<\" sind nicht zusammen erlaubt!\" << endl;\n");
            }
            else
            {
                exclCode.addText("cerr <<  \"" + shortOpt + " und \"<< refValues[exclusions[i]]<<\" sind nicht zusammen erlaubt!\" << endl;\n");
            }

                        exclCode.addText("exitArg = 1;\n");
                    exclCode.endIf();
                exclCode.endForLoop();
            exclCode.endForLoop();

            exclCode.startIf("noRef == 1");
                //exclCode.addText("cerr << \"Es wurde ein Argument übergeben, dass Ref 1-3 nicht zulässt, --help ist somit verboten!\"<< endl;\n");
                exclCode.addText("exitArg = 1;\n");
            exclCode.endIf();

            exclCode.startIf("exitArg != 1");
            if(!ref.empty())
            {
                exclCode.addText("exclusions.push_back(" + ref + ");\n");                                               //Das eigene Argument wird "registriert"
                if(interface != "")
                {
                    exclCode.addText("refValues[" + ref + "] = \"" + interface + "\";");
                } else if (longOpt != "")
                {
                    exclCode.addText("refValues[" + ref + "] = \"" + longOpt + "\";");
                } else
                {
                    exclCode.addText("refValues[" + ref + "] = \"" + shortOpt + "\";");
                }

            }
                exclCode.addText("noRef = 1;\n");
            exclCode.endIf();

        exclusionCheck += ifStateStart;
            exclusionCheck += exclCode.getCode();

            if(hasArguments == "Required" || hasArguments == "optional")
            {
                exclusionCheck +="if(i+1 != argc)\n{\n" + reference + "Str = argv[i+1];\n}\n";                          //Code Generierung um zusätzliche Argumente einzulesen, falls diese Möglich sein sollen
            }
        exclusionCheck += "}\n";



        }
                                                                                                                        ///////////////////////////////////////////////////////////////////////////
        if(hasArguments == "Required")                                                                                  //Code Generierung, um zu überprüfen, ob ein zusätzliches Argument angegeben wurde,
                                                                                                                        //wenn es required ist
        {
            Code pathCheckCode = Code();                                                                                ////pathCheckCode////
                                                                                                                        //Neue Instanz con Code() um zu generierenden Code zwischenzuspeichern

            variableDefinitions += "string " + reference + "Str;\n";

            pathCheckCode.startIf("!" + reference + "Str.empty() && " + reference + "Str.length() > 1");
                pathCheckCode.startIf("(" + reference + "Str.at(0) == '-' && " + reference + "Str.at(1) == '-') || " + reference + "Str.length() <= 1");
                    pathCheckCode.addText("cout << \"--" + longOpt + " benötigt einen Pfad als Argument!\" << endl;\n");
                    pathCheckCode.addText("exitArg = 1;\n");
                pathCheckCode.endIf();
            pathCheckCode.endIf();

            pathCheckCode.startIf(reference +"Str.length() == 1");
                pathCheckCode.addText("cout << \"" +longOpt +" benötigt einen Pfad als Argument!\" << endl;\n");
                pathCheckCode.addText("exitArg = 1;\n");
            pathCheckCode.endIf();

            pathRequiredCheck += pathCheckCode.getCode();
        }
                                                                                                                        /////////////////////////////////////////////////////////////////
        if(!defaultValue.empty())                                                                                          //Code Generierung, falls es default Parameter gibt
        {
            variableDefinitions += "string " + reference + "Str = \"" + defaultValue + "\";\n";
        }
                                                                                                                        //////////////////////////////////////////////////////////////////
                                                                                                                        //Code Generierung für convertToInt mit try-catch
        if(convertTo == "Integer")
        {
            //variableDefinitions += "int " + interface + "Int = 0;\n";
            if(defaultValue != "")
            {
                globalVariables += "int " + reference + "Int = " + defaultValue + ";\n";
                additionalParamVarName = interface + "Int";
            } else
            {
                globalVariables += "int " + reference + "Int = 0;\n";
                additionalParamVarName = interface + "Int";
            }

            string convertInt = "try\n{\n" + reference + "Int = stol(" + reference + "Param);\n}\n";
            additionalParamVarName = reference + "Int";

            convertInt += "catch (invalid_argument const &e)\n{\n";
            convertInt += "cout << \"Bad input: invalid_argument thrown for " + longOpt + ", using default Value if given\" << endl;\n";
            convertInt += "exitArg = 1;\n}\n";

            convertInt += "catch (out_of_range const &e)\n{\n";
            convertInt += "cout << \"Integer overflow: out_of_range thrown for " + longOpt + ", using default Value if given\" << endl;\n";
            convertInt += "exitArg = 1;\n}\n";

            convertToInt += convertInt;
        }                                                                                                               ////////////////////////////////////////////////////////////////////////


        if(convertTo == "bool")
        {
            if(defaultValue != "")
            {
                globalVariables += "bool " + reference + "Bool = " + defaultValue + ";\n";
                additionalParamVarName = interface + "Bool";
            } else
            {
                globalVariables += "int " + reference + "Int = 0;\n";
                additionalParamVarName = interface + "Bool";
            }

            string convertBool = "try\n{\n" + reference + "Bool = " + reference + "Param;\n}\n";
            additionalParamVarName = reference + "Bool";

            convertBool += "catch (exception &e)\n{\n";
            convertBool += "cout << \"Parameter bool von " + longOpt + "konnte nicht konvertiert werden, using default Value if given\" << endl;\n";
            convertBool += "exitArg = 1;\n}\n";
        }

                                                                                       //zum gesamt Code hinzufügen

            if(!shortOpt.empty() && !longOpt.empty())
            {
                printHelpMethodCode += "myPrint(\"-" + shortOpt + ", --" + longOpt + "\\n\", signPerLine);\n";
                printHelpMethodCode += "myPrint(\"" + description + "\\n\\n\", " + signPerLine + ");\n";
            }                                                                                                           //Die Description wird an einen globalen string hinzugefügt für die printHelp Methode

            if(shortOpt.empty() && !longOpt.empty())
            {
                printHelpMethodCode += "myPrint(\"--" + longOpt + "\\n\", signPerLine);\n";
                printHelpMethodCode += "myPrint(\"\t" + description + "\\n\\n\", signPerLine);\n";
            }

            if(!shortOpt.empty() && longOpt.empty())
            {
                printHelpMethodCode += "myPrint(\"--" + shortOpt + "\\n\", " + signPerLine + ");\n";
                printHelpMethodCode += "myPrint(\"\\t\" + description + \\n\\n\", " + signPerLine + ");\n";
            }

            if(!interface.empty())
            {
                globalVariables += "bool bool"+ interface +";\n";
                internalMethod iM;
                if(longOpt != "")
                {
                    iM.methodName = "isSet" + longOpt;
                }
                else
                {
                    iM.methodName = "isSet" + shortOpt;
                }
                if(longOpt == "out-path" || longOpt == "only-if-newer" || longOpt == "astyle-path" || longOpt == "sign-per-line" || longOpt == "no-format")
                {
                    if(shortOpt != "")
                    {
                        iM.methodName = "isSet" + shortOpt; //Da durch das - im Namen Probleme auftreten
                    } else
                    {
                        iM.methodName = "isSet" + interface; //Da durch das - im Namen Probleme auftreten
                    }

                }

                iM.methodCode = "return bool" + interface + ";\n";
                iM.returnType = "bool";

                internalMethods.push_back(iM);



                if(hasArguments != "")
                {
                    if(hasArguments == "Required")
                    {
                        globalVariables += "string " + reference + "Param;\n";
                        additionalParamVarName = interface + "Param";
                    }

                    if(hasArguments == "optional")
                    {
                        globalVariables += "string " + reference + "Param = \"" + defaultValue +"\";\n";
                        additionalParamVarName = interface + "Param";
                    }
                    if(convertTo == "Integer")
                    {
                        additionalParamVarName = reference + "Int";
                        internalMethod iM;
                        iM.returnType = "int";
                        iM.methodCode = "return " + reference + "Int;\n";

                        if(longOpt != "")
                        {
                            iM.methodName = "getValueOf" + longOpt;
                        }
                        else
                        {
                            iM.methodName = "getValueOf" + shortOpt;
                        }
                        if(longOpt == "out-path" || longOpt == "only-if-newer" || longOpt == "astyle-path" || longOpt == "sign-per-line" || longOpt == "no-format")
                        {
                            if(shortOpt != "")
                            {
                                iM.methodName = "getValueOf" + shortOpt; //Da durch das - im Namen Probleme auftreten
                            } else
                            {
                                iM.methodName = "getValueOf" + interface; //Da durch das - im Namen Probleme auftreten
                            }

                        }
                        internalMethods.push_back(iM);
                    }

                    else if(convertTo == "Bool")

                    {
                        additionalParamVarName = interface + "Bool";
                        internalMethod iM;
                        iM.returnType = "int";
                        iM.methodCode = "return bool" + interface + ";";

                        if(longOpt != "")
                        {
                            iM.methodName = "getValueOf" + longOpt;
                        }
                        else
                        {
                            iM.methodName = "getValueOf" + shortOpt;
                        }
                        if(longOpt == "out-path" || longOpt == "only-if-newer" || longOpt == "astyle-path" || longOpt == "sign-per-line" || longOpt == "no-format")
                        {
                            if(shortOpt != "")
                            {
                                iM.methodName = "getValueOf" + shortOpt; //Da durch das - im Namen Probleme auftreten
                            } else
                            {
                                iM.methodName = "getValueOf" + interface; //Da durch das - im Namen Probleme auftreten
                            }

                        }
                        internalMethods.push_back(iM);
                    }
                    else
                    {
                        additionalParamVarName = interface + "Str";
                        internalMethod iM;
                        iM.returnType = "string";
                        iM.methodCode = "return " + reference + "Param;\n";
                        additionalParamVarName = reference + "Param";
                        if(longOpt == "out-path" || longOpt == "only-if-newer" || longOpt == "astyle-path" || longOpt == "sign-per-line" || longOpt == "no-format")
                        {
                            if(shortOpt != "")
                            {
                                iM.methodName = "getValueOf" + shortOpt; //Da durch das - im Namen Probleme auftreten
                            }
                            else if(interface != "")
                            {
                                iM.methodName = "getValueOf" + interface; //Da durch das - im Namen Probleme auftreten
                            }

                        }
                        else if(longOpt != "")
                        {
                            iM.methodName = "getValueOf" + longOpt;
                            variableDefinitions += "bool boolIsSet" + longOpt + ";\n";

                        }
                        else
                        {
                            iM.methodName = "getValueOf" + shortOpt;
                            variableDefinitions += "bool boolIsSet" + shortOpt;
                        }

                        internalMethods.push_back(iM);
                    }

                }

            }

            if(interface == "" && connectToInternalMethod == "" && connectToExternalMethod == "")
            {
                internalMethod iM;
                iM.returnType = "bool";

                if(longOpt != "")
                {
                    iM.methodName = "getValueOf" + longOpt;
                    boolIsSetName = "boolIsSet" + longOpt;
                }
                else
                {
                    iM.methodName = "getValueOf" + shortOpt;
                    boolIsSetName = "boolIsSet" + shortOpt;
                }
                if(longOpt == "out-path" || longOpt == "only-if-newer" || longOpt == "astyle-path" || longOpt == "sign-per-line" || longOpt == "no-format")
                {
                    if(shortOpt != "")
                    {
                        iM.methodName = "getValueOf" + shortOpt; //Da durch das - im Namen Probleme auftreten
                        boolIsSetName = "boolIsSet" + shortOpt;
                    }
                    else
                    {
                        iM.methodName = "getValueOf" + interface; //Da durch das - im Namen Probleme auftreten
                        boolIsSetName = "boolIsSet" + interface;
                    }
                    iM.methodCode = "return " + boolIsSetName + ";";
                }
                internalMethods.push_back(iM);

            }

        Code actOnArgs = Code();

        actOnArgs.startIf(nameCheckBool);
        if(!connectToInternalMethod.empty())                                                                           /////////////////////////////////////////////////////////////////////////
        {                                                                                                           //Code Generierung für connectToInternalMethod
            internalMethod iM = internalMethod();

            iM.methodName = connectToInternalMethod;
            iM.methodCode = "cout << \"" + description + "\" << endl;\n";
            //cout << "METHOD NAME IN I_M: " << iM.methodName << endl;



            if(connectToInternalMethod == "printHelp")
            {
                internalMethods.push_back(iM);
                actOnArgs.addText(connectToInternalMethod + "(signperlineInt);\n"); ///############################HARD CODED nicht gut
                if(!interface.empty())
                {
                    actOnArgs.addText("bool" + interface + " = true;\n");
                }
            }
            else if (hasArguments != "")
            {
                if(additionalParamVarName.at(additionalParamVarName.back()) == 't')
                {
                    iM.expectedVars = "int " + additionalParamVarName;
                }
                if(additionalParamVarName.at(additionalParamVarName.back()) == 'l')
                {
                    iM.expectedVars = "bool " + additionalParamVarName;
                }
                if(additionalParamVarName.at(additionalParamVarName.back()) == 'r')
                {
                    iM.expectedVars = "string " + additionalParamVarName;
                }
                if(additionalParamVarName.at(additionalParamVarName.back()) == 'm')
                {
                    iM.expectedVars = "string " + additionalParamVarName;
                }
                internalMethods.push_back(iM);
                actOnArgs.addText(connectToInternalMethod + "(" + additionalParamVarName  + ");\n");
                if(!interface.empty())
                {
                    actOnArgs.addText("bool" + interface + " = true;\n");
                }
            }

        }
        else
        {
            actOnArgs.addText("cout << \"Es wurde der Parameter --" + longOpt + " erfolgreich übergeben!\" << endl;\n");//Feedback print, wenn ein Argument angegeben wurde
            if(interface != "")
            {
                actOnArgs.addText("bool" + interface + " = true;\n");
            }
            if(!hasArguments.empty())
            {
                actOnArgs.addText("cout << \"Zusätzliche Argumente:\" << " + reference + "Str << endl;\n");      //Zusätzliche Argumente zur Überprüfung mit ausgeben
                actOnArgs.addText(reference + "Param = " + reference + "Str;\n");
                actOnArgs.addText((boolIsSetName + " = true;"));
            }
        }
        actOnArgs.endIf();

        handleArgs += actOnArgs.code;
    }



/*

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

/*    Code code = Code("FileName", "HeaderFileName", "parse", "getOptsParse", "79", "SampleUsage Here", "DER AUTOR");

    code.startForLoop("int i = 1; i<argc; i++");                                                                     //Durch jedes Argument einmal durch

        code.addArgument("1", "h", "help",         "2,3",   "printHelp", "Diese Hilfe ausgeben und beenden", "", "", "", "");
        code.addArgument("2", "v", "version",      "1,3",   "printVersion", "Gibt die Version des Programms aus und beendet", "Version", "", "", "");
        code.addArgument("",  "",  "out-path",     "1,2,3", "",         "Der Pfad wo das Ergebnis hingeneriert werden soll (sonst ins aktuelle Verzeichnis)", "OutputPath", "Required", "", "");
        code.addArgument("",  "",  "astyle-path",  "1,2,3", "",         "Der Pfad wo die Astyle executable gefunden werden kann", "AstylePath", "Required", "", "");
        code.addArgument("",  "",  "sign-per-line","1,2,3", "",         "Die Anzahl der Zeichen pro Linie für den Helptext. Ohne Argument wird der Standartwert genommen.", "SignPerLine", "optional", "Integer", "79");
        code.addArgument("",  "n", "only-if-newer","1,2,3", "",         "Generiert nur wenn die Eingangsdatei neuer ist wie die bereits generierte", "OnlyIfNewer", "", "", "");
        code.addArgument("",  "",  "no-format",    "1,2,3", "",         "Erzeugte Datei wird nicht formatiert", "NoFormat", "", "", "");
        code.addArgument("3", "",  "parse-only",   "1,2",   "ParseXML", "Parst die Datei einmal und beendet das Programm", "", "", "", "");
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


*/